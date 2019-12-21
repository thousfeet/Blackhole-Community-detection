#pragma once

#include "GraphDrawing.h"
#include <iostream>
#include <queue>

class DBScan
{
public:
	DBScan(NodePosSet& nodePoses, int nodeNum, double eps, int minPts, NodeCID& nodeCID);
	void dbscan();

private:
	void init();
	void checkNearPoints();
	bool isCoreObject(int idx);
	void dfs(int now, int c);
	void bfs(int now, int c);
	int nodeNum;
	double eps;
	int minPts;

	const NodePosSet& nodePoses;
	NodeCID& nodeCID;
	NodeNearPoints nodeNearPoints;

	CID clusterIdx;
	ClusterSet clusterSet;
};

