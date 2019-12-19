#include "BlackHole.h"

void BlackHole::exec(const NodeSet& nodes, const EdgeSet& edges, const int dim, NodeCIDSet& nodeCIDs)
{
	NodePosSet nodePoses;
	double a = -0.95, r = -1;
	GraphDrawing::exec(nodes, edges, dim, a, r, nodePoses);
	DBScan::exec(nodes, edges, nodePoses, dim, nodeCIDs);
}
