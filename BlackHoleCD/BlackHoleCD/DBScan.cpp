#include "DBScan.h"
#include <iostream>

using namespace std;


void DBScan::exec(const NodeSet& nodes, const EdgeSet& edges, NodePosSet& nodePoses, const int dim, NodeCIDSet& nodeCIDs)
{
	// Just Place here, you can delete it;
	DataUtils::writeNodePoses(".\\", "test", nodePoses);
}
