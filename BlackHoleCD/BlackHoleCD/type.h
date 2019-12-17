#pragma once

#include <string>
#include <unordered_set>
#include <vector>

typedef int Node;
typedef std::unordered_set<Node> NodeSet;

typedef long long Edge;
typedef std::unordered_set<Edge> EdgeSet;

typedef int CID;
typedef std::vector<CID> Cluster;
typedef std::vector<Cluster> ClusterSet;

typedef std::vector<double> Pos;
typedef std::pair<Node, Pos> NodePos;
typedef std::vector<NodePos> NodePosSet;

typedef std::pair<Node, CID> NodeCID;
typedef std::vector<NodeCID> NodeCIDSet;
