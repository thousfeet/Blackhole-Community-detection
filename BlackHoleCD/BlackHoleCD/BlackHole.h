#pragma once

#include "GraphDrawing.h"
#include "DBScan.h"

class BlackHole
{
public:
	static void exec(const Network& network, const int dim, NodePosSet& nodePoses, NodeCID& nodeCID);
};

