#include "DBScan.h"
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

#define NOT_CLASSIFIED -1
#define NOISE -2
#define PI 3.141592653


class point {
public:
	double x;
	double y;
};


DBScan::DBScan(NodePosSet& nodePoses, int nodeNum, double removePercentage, int minPts, NodeCID& nodeCID)
	: nodePoses(nodePoses), nodeCID(nodeCID), minPts(minPts), nodeNum(nodeNum)
{
	this->nodeCID.clear();
	this->eps = getEps(removePercentage);
	this->clusterIdx = -1;

	/*auto& p = nodePoses.begin()->second;
	Pos maxPos(p), minPos(p);
	int dim = p.getDim();
	for (auto& t : nodePoses) {
		for (int i = 0; i < dim; ++i) {
			maxPos[i] = max(maxPos[i], t.second[i]);
			minPos[i] = min(maxPos[i], t.second[i]);
		}
	}
	for (int i = 0; i < dim; ++i)
		this->eps *= maxPos[i] - minPos[i];*/
		//cout << "eps = " << this->eps << endl;
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
			//std::cout << "find new cluster ID: " << clusterIdx << std::endl;
			//dfs(i, clusterIdx);
			bfs(i, clusterIdx);
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

	cout << "[Cluster Count]" << clusterIdx << endl;

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
			if ((node1.second - node2.second).eucDis() <= eps) {
				nodeNearPoints[i].insert(j);
			}
		}
	}
}

bool DBScan::isCoreObject(int idx)
{
	return nodeNearPoints[idx].size() >= 1;
	// return nodeNearPoints[idx].size() >= minPts;
}

void DBScan::dfs(int now, int c)
{
	nodeCID[now] = c;
	if (!isCoreObject(now)) return;

	stack<pair<NodeSet::const_iterator, NodeSet::const_iterator>> S;
	S.push({ nodeNearPoints[now].begin(), nodeNearPoints[now].end() });

	while (!S.empty()) {
		auto& t = S.top();
		Node next = *t.first;
		if (++t.first == t.second)
			S.pop();
		if (nodeCID[next] == NOISE)
			nodeCID[next] = c;
		if (nodeCID[next] != NOT_CLASSIFIED)
			continue;
		nodeCID[next] = c;
		if (isCoreObject(next))
			S.push({ nodeNearPoints[next].begin(), nodeNearPoints[next].end() });
	}
}

void DBScan::bfs(int now, int c)
{
	nodeCID[now] = c;
	queue<int> que;
	que.push(now);
	while (!que.empty()) {
		int t = que.front();
		que.pop();
		for (auto& next : nodeNearPoints[t]) {
			if (nodeCID[next] == NOISE) nodeCID[next] = c;
			if (nodeCID[next] != NOT_CLASSIFIED) continue;
			nodeCID[next] = c;
			if (isCoreObject(next)) que.push(next);
		}
	}
}

double DBScan::getEps(double removePercentage)
{
	double* dist_vec = new double[nodeNum];
	double* dist_sorted = new double[nodeNum];
	double eps;
	int i = 0;

	for (const auto& it : nodePoses) {
		int j = 0;
		for (const auto& jt : nodePoses) {
			dist_sorted[j] = (jt.second - it.second).length();
			++j;
		}
		std::sort(dist_sorted, dist_sorted + nodeNum);
		dist_vec[i] = dist_sorted[minPts - 1];
		++i;
	}

	std::sort(dist_vec, dist_vec + nodeNum, std::greater< double>());

	double trunc = (nodeNum * removePercentage);
	int tr = (int)trunc;
	std::cout << "Truncated # = " << tr << std::endl;

	for (int i = 0; i < tr; i++) {
		dist_vec[i] = 0;
	}

	std::sort(dist_vec, dist_vec + nodeNum, std::greater< double>());

	point* original = new point[nodeNum];
	for (int i = 0; i < nodeNum; i++) {
		original[i].x = i;
		original[i].y = dist_vec[i];
	}

	//find minVal, maxVal of Y
	double maxVal = -1;
	double minVal = 999999;
	for (int i = 0; i < nodeNum; i++) {
		if (original[i].y >= maxVal) {
			maxVal = original[i].y;
		}
		if (original[i].y <= minVal) {
			minVal = original[i].y;
		}
	}
	//min-max normalization
	for (int i = 0; i < nodeNum; i++) {
		original[i].x = ((original[i].x - 0) / nodeNum) * 1;
		original[i].y = ((original[i].y - minVal) / (maxVal - minVal));
	}

	//rotation
	for (int i = 0; i < nodeNum; i++) {
		original[i].x = cos(-PI / 4.0f) * original[i].x + sin(-PI / 4.0f) * (original[i].y - 1.0f);
		original[i].y = -sin(-PI / 4.0f) * original[i].x + cos(-PI / 4.0f) * (original[i].y - 1.0f);
	}

	minVal = 999999;
	int minValueIdx = -1;
	for (int i = 0; i < nodeNum; i++) {
		if (original[i].y <= minVal) {
			minVal = original[i].y;
			minValueIdx = i;
		}
	}

	std::cout << "Approximated Value for DBSCAN = " << dist_vec[minValueIdx] << std::endl;
	eps = dist_vec[minValueIdx];
	delete[] dist_sorted;
	delete[] dist_vec;
	delete[] original;
	return eps;
}

