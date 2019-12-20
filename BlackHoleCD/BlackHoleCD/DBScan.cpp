#include "DBScan.h"
#include <iostream>

using namespace std;


void DBScan::exec(NodePosSet& nodePoses, const int dim, NodeCIDSet& nodeCIDs)
{
	// Just Place here, you can delete it;
	DataUtils::writeNodePoses(".\\", "test", nodePoses);
	string filename = "test.nodePoses.txt";
	string dataname = "..\\..\\Datasets\\Football\\football.ungraph.txt";
	system(("python draw.py " + dataname + " " + filename).c_str());
}
