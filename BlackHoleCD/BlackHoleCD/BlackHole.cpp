#include "BlackHole.h"

void BlackHole::exec(const Network& network, const int dim, NodeCIDSet& nodeCIDs)
{
	NodePosSet nodePoses;
	// double a = -0.95, r = -1;
	double a = 0.01, r = 0.0;
	GraphDrawing graphDrawing = GraphDrawing(dim, a, r, 100);
	graphDrawing.exec(network, nodePoses);
	DBScan dbscan(nodePoses, network.getNodeNum(), 0.1, 5);
	dbscan.dbscan();
	// DBScan::exec(nodePoses, dim, nodeCIDs);
}
