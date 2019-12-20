#include "Network.h"

Network::Network()
	: allDegree(0)
{
}

void Network::insertEdge(Node v1, Node v2)
{
	nodes.insert(v1);
	nodes.insert(v2);
	edges.insert(EDGE(v1, v2));
	allDegree += 2;
	degMat[v1] += 1;
	degMat[v2] += 1;
}

void Network::clear()
{
	nodes.clear();
	edges.clear();
	degMat.clear();
}

const NodeSet& Network::getNodeSet() const
{
	return nodes;
}

const EdgeSet& Network::getEdgeSet() const
{
	return edges;
}

int Network::getNodeNum() const
{
	return (int)nodes.size();
}

int Network::getEdgeNum() const
{
	return (int)edges.size();
}

double Network::getFactor(Node u, Node v) const
{
	return double(degMat.find(u)->second) * double(degMat.find(v)->second) / allDegree;
}
