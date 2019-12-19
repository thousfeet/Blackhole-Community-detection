#pragma once

#include "GraphDrawing.h"

class DBScan
{
public:
	/*
	dbscan函数说明

	作用：DBScan聚类
	输入：nodePoses：vector<pair<节点，Pos>>， 
	输出：nodeCIDs：vector<pair<节点, 所属的Cluster>>
	*/
	static NodeCIDSet dbscan(NodePosSet& nodePoses, const float eps, const int minPts);
};

