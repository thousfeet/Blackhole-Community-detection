#include "BlackHole.h"

void BlackHole::exec(const Network& network, const int dim, NodePosSet& nodePoses, NodeCID& nodeCID)
{
	nodePoses.clear();
	// double a = -0.95, r = -1;
	double a = 0.01, r = 0.0;
	GraphDrawing graphDrawing = GraphDrawing(dim, a, r, 100);
	graphDrawing.exec(network, nodePoses);
	DBScan dbscan(nodePoses, network.getNodeNum(), 1.5, 1, nodeCID);
	dbscan.dbscan();
}
