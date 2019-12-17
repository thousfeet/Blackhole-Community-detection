#include "BlackHole.h"

void BlackHole::exec(const NodeSet& nodes, const EdgeSet& edges, const int dim, NodeCIDSet& nodeCIDs)
{
	NodePosSet nodePoses;
	GraphDrawing::exec(nodes, edges, dim, nodePoses);
	DBScan::exec(nodePoses, dim, nodeCIDs);
}
