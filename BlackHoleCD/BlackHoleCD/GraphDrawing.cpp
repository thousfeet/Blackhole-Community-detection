#include "GraphDrawing.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

GraphDrawing::GraphDrawing(const int dim, const double a, const double r, int nIters)
	: dim(dim), a(a), r(r), fa(a), fr(r), nIters(nIters)
{
}

void GraphDrawing::exec(const Network& network, NodePosSet& nodePoses)
{
	clock_t start = clock();
	const NodeSet& nodes = network.getNodeSet();
	const EdgeSet& edges = network.getEdgeSet();
	for (const Node node : nodes)
		nodePoses[node] = getRandomPos();
	// TODO OctTree
	unordered_map<Node, Pos> fs;
	Pos tf(dim);
	double oldEnergy = calEnergy(network, a, r, nodePoses);
	cout << "initEnergy = " << oldEnergy << endl;
	int iter = 0;
	while (true) {
		updateParam(++iter);
		for (const Edge edge : edges) {
			Node v1 = V1(edge), v2 = V2(edge);
			calAttractiveForce(nodePoses[v1], nodePoses[v2], a, tf);
			if (fs.count(v1))
				fs[v1] += tf;
			else
				fs[v1] = tf;
			calAttractiveForce(nodePoses[v2], nodePoses[v1], a, tf);
			if (fs.count(v2))
				fs[v2] += tf;
			else
				fs[v2] = tf;
		}

		/*for (int i = 1; i < 3; ++i) {
			cout << "(";
			for (int j = 0; j < dim; ++j) {
				cout << fs[i][j] << ' ';
			}
			cout << ") ";
		}
		cout << endl;*/

		// TODO OctTree
		for (const Node v1 : nodes) {
			for (const Node v2 : nodes) {
				calRepulsiveForce(nodePoses[v1], nodePoses[v2], r, tf);
				fs[v1] += tf * network.getFactor(v1, v2);
			}
		}

		double minEnergy = calEnergy(network, a, r, nodePoses);
		int bestGamma = -1;
		int maxGamma = 1 << 6;
		for (int gamma = 1; gamma <= maxGamma; gamma <<= 1) {
			NodePosSet newPoses = nodePoses;
			double rGamma = 1.0 / double(gamma);
			for (const Node node : nodes)
				newPoses[node] += fs[node] * rGamma;
			double energy = calEnergy(network, a, r, newPoses);
			if (bestGamma = -1 || energy < minEnergy) {
				bestGamma = gamma;
				minEnergy = energy;
			}
		}

		if (bestGamma != -1) {
			double gamma = 1.0 / double(bestGamma);
			for (const Node node : nodes)
				nodePoses[node] += fs[node] * gamma;
		}
		cout << "[iter = " << iter << "] gamma = " << bestGamma << ", energy = " << minEnergy << ", a = " << a << ", r = " << r << endl;
		/*if (abs(oldEnergy - minEnergy) < 1e-6)
			break;*/
		if (iter > nIters)
			break;
		oldEnergy = minEnergy;
	}
	clock_t end = clock();
	cout << "[GraphDrawing::exec] [" << double(end - start) / CLOCKS_PER_SEC << "s] iter = " << iter << endl;
}

Pos GraphDrawing::getRandomPos()
{
	Pos p(dim);
	for (int i = 0; i < dim; ++i)
		p[i] = double(rand() + 1) / RAND_MAX - 0.5;
	return p;
}

void GraphDrawing::calAttractiveForce(const Pos& u, const Pos& v, const double a, Pos& fa)
{
	fa = v - u;
	double dst = fa.length();
	/*if (abs(dst) < 1e-6)
		return;*/
	fa *= pow(dst, a - 2);
}

void GraphDrawing::calRepulsiveForce(const Pos& u, const Pos& v, const double r, Pos& fr)
{
	fr = u - v;
	double dst = fr.length();
	if (abs(dst) < 1e-6)
		return;
	fr *= pow(dst, r - 2);
}

double GraphDrawing::calEnergy(const Network& network, const double a, const double r, NodePosSet& nodePoses)
{
	return calAttractiveEnergy(network.getEdgeSet(), a, nodePoses) - calRepulsiveEnergy(network, r, nodePoses);
}

double GraphDrawing::calEnergy(const Pos& pu, const Pos& pv, const double p)
{
	double dst = (pu - pv).length();
	if (abs(dst) < 1e-6)
		return 0.0;
	return abs(p) < 1e-6 ? log(dst) : pow(dst, p) / p;
}

double GraphDrawing::calAttractiveEnergy(const EdgeSet& edges, const double a, NodePosSet& nodePoses)
{
	double energy = 0.0;
	for (const Edge edge : edges) {
		Node u = V1(edge), v = V2(edge);
		energy += calEnergy(nodePoses[u], nodePoses[v], a);
		energy += calEnergy(nodePoses[v], nodePoses[u], a);
	}
	return energy;
}



double GraphDrawing::calRepulsiveEnergy(const Network& network, const double r, NodePosSet& nodePoses)
{
	const NodeSet& nodes = network.getNodeSet();
	double energy = 0.0;
	for (const Node u : nodes) {
		for (const Node v : nodes)
			energy += network.getFactor(u, v) * calEnergy(nodePoses[u], nodePoses[v], r);
	}
	return energy;
}

void GraphDrawing::updateParam(const int iter)
{
	if (nIters >= 50 && fr < 1.0) {
		a = fa;
		r = fr;

		if (iter <= 0.6 * nIters) {
			// use energy model with few local minima 
			a = a + 1.1 * (1.0 - fr);
			r = r + 0.9 * (1.0 - fr);
		}
		else if (iter <= 0.9 * nIters) {
			a = a + 1.1 * (1.0 - fr) * (0.9 - ((double)iter) / nIters) / 0.3;
			r = r + 0.9 * (1.0 - fr) * (0.9 - ((double)iter) / nIters) / 0.3;
		}
	}
}

