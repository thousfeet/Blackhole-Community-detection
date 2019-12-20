#pragma once

#include "GraphDrawing.h"
#include <iostream>

class DBScan
{
public:

	DBScan(NodePosSet& nodePoses, int nodeNum, float eps, int minPts);
	void dbscan();

private:
	void init();
	void checkNearPoints();
	bool isCoreObject(int idx);
	void dfs(int now, int c);
	int nodeNum;
	float eps;
	int minPts;

	NodePosSet nodePoses;
	NodeCID nodeCID;
	NodeNearPoints nodeNearPoints;

	CID clusterIdx;
	ClusterSet clusterSet;
};

