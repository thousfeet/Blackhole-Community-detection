#pragma once

#include "DataUtils.h"

typedef std::pair<Node, Pos> NodePos;

class OctTree
{
public:
	OctTree(const int dim, const NodePosSet& nodes);

private:
	union NodeData {
		OctTree* tr;
		NodePos* np;
	};
};

