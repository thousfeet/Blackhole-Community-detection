#pragma once

#include "DataUtils.h"

class DBScan
{
public:
	static void exec(NodePosSet& nodePoses, const int dim, NodeCIDSet& nodeCIDs);
};

