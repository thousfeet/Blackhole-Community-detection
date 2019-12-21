#pragma once

#include <unordered_set>
#include <unordered_map>

#define max(a, b) (a < b ? b : a)
#define min(a, b) (a < b ? a : b)

typedef unsigned int Node;
typedef std::unordered_set<Node> NodeSet_;
typedef std::vector<Node> NodeSet;

typedef unsigned long long Edge;
typedef std::unordered_set<Edge> EdgeSet_;
typedef std::vector<Edge> EdgeSet;

#define EDGE(v1, v2) (v1 < v2 ? ((Edge(v1) << 32) | v2) : ((Edge(v2) << 32) | v1))
#define V1(edge) (Node((edge >> 32) & 0xffffffff))
#define V2(edge) (Node(edge & 0xffffffff))

class Network
{
public:
	Network();

public:
	void insertEdge(Node v1, Node v2);
	void clear();

public:
	const NodeSet& getNodeSet() const;
	const EdgeSet& getEdgeSet() const;
	int getNodeNum() const;
	int getEdgeNum() const;
	double getFactor(Node u, Node v) const;
	double getFactor(Node u) const;
	int getNodeDegree(Node u) const;
	void readFinish();

private:
	NodeSet_ nodes_;
	NodeSet nodes;
	EdgeSet_ edges_;
	EdgeSet edges;
	std::unordered_map<Node, int> degMat;
	int allDegree;
	Node maxNodeId;
};

