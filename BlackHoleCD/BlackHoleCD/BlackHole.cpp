#include "BlackHole.h"
#include <ctime>

using namespace std;

void BlackHole::exec(const Network& network, const int dim, NodePosSet& nodePoses, NodeCID& nodeCID)
{
	clock_t start = clock();
	nodePoses.clear();
	// double a = -0.95, r = -1;
	double a = 0.01, r = 0.0;
	GraphDrawing graphDrawing = GraphDrawing(dim, a, r, 100);
	graphDrawing.exec(network, nodePoses);
	DBScan dbscan(nodePoses, network.getNodeNum(), 0.01, 1, nodeCID);
	dbscan.dbscan();
	clock_t end = clock();
	cout << "[BlackHole::exec] [" << double(end - start) / CLOCKS_PER_SEC << "s]" << endl;
}
