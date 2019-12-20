#pragma once

#include <string>
#include "Pos.h"
#include "Network.h"


/********************************************
类型说明

Node - unsigned int: 节点ID
NodeSet - unordered_set: Node集合

Edge - long long: 边权
EdgeSet - unordered_set: Edge集合

CID - int: Cluster的ID
ClusterSet - unordered_map: <CID, NodeSet>

Pos - vector: {<double>} 节点在空间中的位置
NodePosSet - unordered_map: <Node, Pos>

NodeCID - unordered_map: <Node, CID> 节点所属的cluster
NodeNearPoints - unordered_map: <Node, NodeSet>
***********************************************/


typedef int CID;
typedef std::unordered_map<CID, NodeSet> ClusterSet;

typedef std::unordered_map<Node, Pos> NodePosSet;
typedef std::unordered_map<Node, CID> NodeCID;

typedef std::unordered_map<Node, Pos> NodePosSet;
typedef std::unordered_map<Node, NodeSet> NodeNearPoints;
