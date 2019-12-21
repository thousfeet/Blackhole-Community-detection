#pragma once

#include "DataUtils.h"

typedef std::vector<Node> NodeVec;

class OctTree
{
public:
	OctTree(const int dim, const NodePosSet& nodePoses);
	~OctTree();

public:
	void assign(const Network& network, const NodeVec& nodes, int depth);
	int depth() const;
	int count() const;
	double width() const;

private:
	bool checkSplit(const Network& network, const NodeVec& nodes);
	int getIndex(Node node) const;

public:
	union NodeData {
		NodeData(Node np) : np(np) {}
		NodeData(OctTree* tr) : tr(tr) {}
		OctTree* tr;
		Node np;
	};

	enum { MAX_DEPTH = 18 };
	const int dim;
	const int nMaxChild;
	std::vector<NodeData> data;
	bool isLeaf;
	Pos maxPos;
	Pos minPos;
	Pos massCenter;
	Pos regionCenter;
	int weight;
	const NodePosSet& nodePoses;
};

