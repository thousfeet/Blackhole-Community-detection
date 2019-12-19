#include "GraphDrawing.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void GraphDrawing::exec(const NodeSet& nodes, const EdgeSet& edges, const int dim, const double a, const double r, NodePosSet& nodePoses)
{
	clock_t start = clock();
	for (const Node node : nodes)
		nodePoses[node] = getRandomPos(dim);
	// TODO OctTree
	unordered_map<Node, Pos> fs;
	Pos tf(dim);
	double oldEnergy = calEnergy(nodes, edges, dim, a, r, nodePoses);
	int iter = 0;
	while (true) {
		for (const Edge edge : edges) {
			Node v1 = V1(edge), v2 = V2(edge);
			calAttractiveForce(dim, nodePoses[v1], nodePoses[v2], a, tf);
			if (fs.count(v1))
				fs[v1] += tf;
			else
				fs[v1] = tf;
			calAttractiveForce(dim, nodePoses[v2], nodePoses[v1], a, tf);
			if (fs.count(v2))
				fs[v2] += tf;
			else
				fs[v2] = tf;
		}

		// TODO OctTree
		double node_factor = 1.0 / double(nodes.size());
		for (const Node v1 : nodes) {
			for (const Node v2 : nodes) {
				calRepulsiveForce(dim, nodePoses[v1], nodePoses[v2], a, tf);
				fs[v1] += tf * node_factor;
				calRepulsiveForce(dim, nodePoses[v2], nodePoses[v1], a, tf);
				fs[v2] += tf * node_factor;
			}
		}

		double minEnergy = oldEnergy;
		int bestGamma = -1;
		int maxGamma = 1 << 6;
		for (int gamma = 1; gamma <= maxGamma; gamma <<= 1) {
			NodePosSet newPoses = nodePoses;
			double rGamma = 1.0 / double(gamma);
			for (const Node node : nodes)
				newPoses[node] += fs[node] * rGamma;
			double energy = calEnergy(nodes, edges, dim, a, r, newPoses);
			if (energy < minEnergy) {
				bestGamma = gamma;
				minEnergy = energy;
			}
		}

		if (bestGamma != -1) {
			double gamma = 1.0 / double(bestGamma);
			for (const Node node : nodes)
				nodePoses[node] += fs[node] * gamma;
		}
		++iter;
		cout << "[iter = " << iter << "] gamma = " << bestGamma << ", energy = " << minEnergy << endl;
		if (abs(oldEnergy - minEnergy) < 1e-6)
			break;
		oldEnergy = minEnergy;
	}
	clock_t end = clock();
	cout << "[GraphDrawing::exec] [" << double(end - start) / CLOCKS_PER_SEC << "s] iter = " << iter << endl;
}

Pos GraphDrawing::getRandomPos(const int dim)
{
	Pos p(dim);
	for (int i = 0; i < dim; ++i)
		p[i] = double(rand() + 1) / RAND_MAX - 0.5;
	return p;
}

void GraphDrawing::calAttractiveForce(const int dim, const Pos& u, const Pos& v, const double a, Pos& fa)
{
	fa = v - u;
	double dst = fa.length();
	/*if (abs(dst) < 1e-6)
		return;*/
	fa *= pow(dst, a);
}

void GraphDrawing::calRepulsiveForce(const int dim, const Pos& u, const Pos& v, const double r, Pos& fr)
{
	fr = u - v;
	double dst = fr.length();
	if (abs(dst) < 1e-6)
		return;
	fr *= pow(dst, r);
}

double GraphDrawing::calEnergy(const NodeSet& nodes, const EdgeSet& edges, const int dim, const double a, const double r, NodePosSet& nodePoses)
{
	return calAttractiveEnergy(edges, dim, a, nodePoses) - calRepulsiveEnergy(nodes, dim, r, nodePoses);
}

double GraphDrawing::calEnergy(const Pos& pu, const Pos& pv, const double p)
{
	double dst = (pu - pv).length();
	if (abs(dst) < 1e-6)
		return 0.0;
	return abs(p + 1) < 1e-6 ? log(dst) : pow(dst, p + 1) / (p + 1);
}

double GraphDrawing::calAttractiveEnergy(const EdgeSet& edges, const int dim, const double a, NodePosSet& nodePoses)
{
	double energy = 0.0;
	for (const Edge edge : edges) {
		Node u = V1(edge), v = V2(edge);
		energy += calEnergy(nodePoses[u], nodePoses[v], a);
		energy += calEnergy(nodePoses[v], nodePoses[u], a);
	}
	return energy;
}



double GraphDrawing::calRepulsiveEnergy(const NodeSet& nodes, const int dim, const double r, NodePosSet& nodePoses)
{
	double energy = 0.0;
	for (const Node u : nodes)
		for (const Node v : nodes)
			energy += calEnergy(nodePoses[u], nodePoses[v], r);
	return energy;
}

