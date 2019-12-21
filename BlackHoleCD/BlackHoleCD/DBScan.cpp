#include "DBScan.h"
#include <string>

using namespace std;

#define NOT_CLASSIFIED -1
#define NOISE -2


DBScan::DBScan(NodePosSet& nodePoses, int nodeNum, double eps, int minPts, NodeCID& nodeCID)
	: nodePoses(nodePoses), nodeCID(nodeCID)
{
	this->nodeCID.clear();
	this->eps = eps;
	this->minPts = minPts;
	this->nodeNum = nodeNum;
	this->clusterIdx = -1;

	auto& p = nodePoses.begin()->second;
	Pos maxPos(p), minPos(p);
	int dim = p.getDim();
	for (auto& t : nodePoses) {
		for (int i = 0; i < dim; ++i) {
			maxPos[i] = max(maxPos[i], t.second[i]);
			minPos[i] = min(maxPos[i], t.second[i]);
		}
	}
	for (int i = 0; i < dim; ++i)
		this->eps *= maxPos[i] - minPos[i];
	cout << "eps = " << this->eps << endl;
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
	for (auto& node1 : nodePoses) {
		auto i = node1.first; //node ID
		for (auto& node2 : nodePoses) {
			auto j = node2.first; //node ID
			if (i == j) continue;
			// cout << (node1.second - node2.second).eucDis() << endl;
			if ((node1.second - node2.second).eucDis() <= eps) {
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
	if (!isCoreObject(now))
		return;
	for (auto& next : nodeNearPoints[now]) {
		if(nodeCID[next] == NOISE) nodeCID[next] = c;
		if (nodeCID[next] != NOT_CLASSIFIED) continue; 
		dfs(next, c);

	}
}