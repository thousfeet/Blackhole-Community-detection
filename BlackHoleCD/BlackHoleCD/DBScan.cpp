#include "DBScan.h"
#include <string>

using namespace std;

#define NOT_CLASSIFIED -1
#define NOISE -2


DBScan::DBScan(NodePosSet& nodePoses, int nodeNum, float eps, int minPts)
	: nodePoses(nodePoses)
{
	this->eps = eps;
	this->minPts = minPts;
	this->nodeNum = nodeNum;
	this->clusterIdx = -1;
}

void DBScan::dbscan()
{
	init();
	checkNearPoints();

	for (auto node : nodePoses) {
		auto i = node.first; //node ID
		if (nodeCID[i] != NOT_CLASSIFIED) continue;

		if (isCoreObject(i)) {
			clusterIdx++;
			std::cout << "find new cluster ID: " << clusterIdx << std::endl;
			dfs(i, clusterIdx);
		}
		else {
			nodeCID[i] = NOISE;
		}
	}

	for (auto node : nodePoses) {
		auto i = node.first; //node ID
		if (nodeCID[i] != NOISE) {
			clusterSet[nodeCID[i]].insert(i);
		}
	}

	DataUtils::writeNodePoses(".\\", "test", nodePoses);
}

void DBScan::init()
{
	for (auto node : nodePoses) {
		auto nodeID = node.first;
		nodeCID[nodeID] = NOT_CLASSIFIED;
	}
}

void DBScan::checkNearPoints()
{
	for (auto node : nodePoses) {
		auto i = node.first; //node ID
		for (auto node : nodePoses) {
			auto j = node.first; //node ID
			if (i == j) continue;
			if ((nodePoses[i] - nodePoses[j]).eucDis() <= eps) {
				nodeNearPoints[i].insert(j);
			}
		}
	}
}

bool DBScan::isCoreObject(int idx)
{
	return nodeNearPoints[idx].size() >= minPts;
}

void DBScan::dfs(int now, int c)
{
	nodeCID[now] = c;
	if (!isCoreObject(now)) return;

	for (auto& next : nodeNearPoints[now]) {
		if (nodeCID[next] != NOT_CLASSIFIED) continue; //not correct£¡
		dfs(next, c);
	}

}

void DBScan::exec(NodePosSet& nodePoses, const int dim, NodeCIDSet& nodeCIDs)
{
	// Just Place here, you can delete it;
	DataUtils::writeNodePoses(".\\", "test", nodePoses);
	string filename = "test.nodePoses.txt";
	string dataname = "..\\..\\Datasets\\Football\\football.ungraph.txt";
	system(("python draw.py " + dataname + " " + filename).c_str());
}
