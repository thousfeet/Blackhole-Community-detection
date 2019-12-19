#pragma once

#include "DataUtils.h"

class DBScan
{
public:
	static void exec(const NodeSet& nodes, const EdgeSet& edges, NodePosSet& nodePoses, const int dim, NodeCIDSet& nodeCIDs);
};

