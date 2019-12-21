#pragma once

#include <string>
#include "Pos.h"
#include "Network.h"


/********************************************
����˵��

Node - unsigned int: �ڵ�ID
NodeSet - unordered_set: Node����

Edge - long long: ��Ȩ
EdgeSet - unordered_set: Edge����

CID - int: Cluster��ID
ClusterSet - unordered_map: <CID, NodeSet>

Pos - vector: {<double>} �ڵ��ڿռ��е�λ��
NodePosSet - unordered_map: <Node, Pos>

NodeCID - unordered_map: <Node, CID> �ڵ�������cluster
NodeNearPoints - unordered_map: <Node, NodeSet>
***********************************************/


typedef int CID;
typedef std::unordered_map<CID, NodeSet> ClusterSet;

typedef std::unordered_map<Node, Pos> NodePosSet;
typedef std::unordered_map<Node, CID> NodeCID;

typedef std::unordered_map<Node, Pos> NodePosSet;
typedef std::unordered_map<Node, NodeSet> NodeNearPoints;
