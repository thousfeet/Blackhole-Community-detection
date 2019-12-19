#pragma once

#include "DataUtils.h"

class DBScan
{
public:
	/*
	dbscan����˵��

	���ã�DBScan����
	���룺nodePoses��vector<pair<�ڵ㣬Pos>>�� 
	�����nodeCIDs��vector<pair<�ڵ�, ������Cluster>>
	*/
	static NodeCIDSet dbscan(const NodePosSet& nodePoses, const float eps, const int minPts);
};

