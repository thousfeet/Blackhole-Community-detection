#include "OctTree.h"
#include <iostream>
using namespace std;

// #define THETA 1e-6
#define THETA 20

OctTree::OctTree(const int dim, const NodePosSet& nodePoses)
	: dim(dim), nMaxChild(1 << (dim + 1)), isLeaf(true), maxPos(dim),
	minPos(dim), massCenter(dim), weight(0), nodePoses(nodePoses), regionCenter(dim)
{
}

OctTree::~OctTree()
{
	if (!isLeaf) {
		for (NodeData nd : data)
			delete nd.tr;
	}
}

void OctTree::assign(const Network& network, const NodeVec& nodes, int depth)
{
	if (nodes.empty())
		return;

	if (!checkSplit(network, nodes) || depth >= MAX_DEPTH) {
		data.clear();
		isLeaf = true;
		for (Node node : nodes)
			data.push_back(node);
		return;
	}
	
	data.assign(nMaxChild, nullptr);
	vector<NodeVec> childNodes(nMaxChild);
	isLeaf = false;
	for (Node node : nodes) {
		int cidx = getIndex(node);
		childNodes[cidx].push_back(node);
	}
	for (int i = 0; i < nMaxChild; ++i) {
		if (!childNodes[i].empty()) {
			data[i].tr = new OctTree(dim, nodePoses);
			data[i].tr->assign(network, childNodes[i], depth + 1);
		}
	}
}

int OctTree::depth() const
{
	if (isLeaf)
		return 1;
	int d = 0;
	for (NodeData nd : data)
		d = max(d, nd.tr->depth());
	return d + 1;
}

int OctTree::count() const
{
	if (isLeaf)
		return (int)data.size();
	int d = 0;
	for (NodeData nd : data)
		d += nd.tr->count();
	return d;
}

double OctTree::width() const
{
	double s = 0;
	for (int i = 0; i < dim; ++i)
		s = max(s, maxPos[i] - minPos[i]);
	return s * 1.414;
}

bool OctTree::checkSplit(const Network& network, const NodeVec& nodes)
{
	maxPos = minPos = nodePoses.find(nodes[0])->second;
	weight = 0;
	massCenter.setZero();
	for (Node node : nodes) {
		const Pos& p = nodePoses.find(node)->second;
		int nodeDegree = network.getNodeDegree(node);
		weight += nodeDegree;
		massCenter += p * nodeDegree;
		for (int i = 0; i < dim; ++i) {
			maxPos[i] = max(maxPos[i], p[i]);
			minPos[i] = min(minPos[i], p[i]);
		}
	}
	massCenter /= weight;
	double s = 0;
	for (int i = 0; i < dim; ++i)
		s = max(s, maxPos[i] - minPos[i]);
	regionCenter = (maxPos + minPos) / 2.0;
	double d = (regionCenter - massCenter).length();
	// return nodes.size() != 1;
	return (s / d > THETA);
}

int OctTree::getIndex(Node node) const
{
	int childIndex = 0;
	const Pos& p = nodePoses.find(node)->second;
	for (int i = 0; i < dim; ++i)
		if (p[i] > regionCenter[i])
			childIndex += 1 << i;
	return childIndex;
}
