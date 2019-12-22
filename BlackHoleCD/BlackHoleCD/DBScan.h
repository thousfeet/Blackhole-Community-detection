#pragma once

#include "GraphDrawing.h"
#include <iostream>
#include <queue>

class DBScan
{
public:
	DBScan(NodePosSet& nodePoses, int nodeNum, int minPts, NodeCID& nodeCID);
	void dbscan();

private:
	void init();
	void checkNearPoints();
	bool isCoreObject(int idx);
	void dfs(int now, int c);
	void bfs(int now, int c);
	double getEps(double removePercentage);
	int nodeNum;
	double eps;
	int minPts;

	const NodePosSet& nodePoses;
	NodeCID& nodeCID;
	NodeNearPoints nodeNearPoints;

	CID clusterIdx;
	ClusterSet clusterSet;
};

