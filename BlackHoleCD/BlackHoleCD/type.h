#pragma once

#include <string>
#include "Pos.h"
#include "Network.h"


typedef unsigned int CID;
typedef std::vector<CID> Cluster;
typedef std::vector<Cluster> ClusterSet;

typedef std::unordered_map<Node, Pos> NodePosSet;
typedef std::pair<Node, CID> NodeCID;
typedef std::vector<NodeCID> NodeCIDSet;
