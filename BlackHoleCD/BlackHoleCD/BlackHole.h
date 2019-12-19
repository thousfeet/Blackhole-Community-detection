#pragma once

#include "GraphDrawing.h"
#include "DBScan.h"

class BlackHole
{
public:
	static void exec(const NodeSet& nodes, const EdgeSet& edges, const int dim, NodeCIDSet& nodeCIDs);
};

