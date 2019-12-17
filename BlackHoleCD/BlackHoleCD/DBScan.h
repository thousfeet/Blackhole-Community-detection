#pragma once

#include "GraphDrawing.h"

class DBScan
{
public:
	static void exec(const NodePosSet& nodePoses, const int dim, NodeCIDSet& nodeCIDs);
};

