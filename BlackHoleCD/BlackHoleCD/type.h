#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>


/********************************************
类型说明

Node - unsigned int: 节点ID
NodeSet - unordered_set: Node集合

Edge - long long: 边权
EdgeSet - unordered_set: Edge集合

CID - int: Cluster的ID
Cluster - vector: Cluster的ID集合
ClusterSet - vector: Cluster集合？

Pos - vector: {<double>} 节点在空间中的位置
NodePos - pair: <节点，Pos>
NodePosSet - vector: NodePos集合

NodeCID - pair: <节点, 所属的Cluster>
NodeCIDSet - vector: NodeCID集合
***********************************************/

typedef unsigned int Node;
typedef std::unordered_set<Node> NodeSet;

typedef unsigned long long Edge;
typedef std::unordered_set<Edge> EdgeSet;

typedef unsigned int CID;
typedef std::vector<CID> Cluster;
typedef std::vector<Cluster> ClusterSet;

class Pos {
public:
	Pos();
	Pos(const int dim);
	Pos(const Pos& t);

public:
	Pos operator+(const Pos& t) const;
	Pos operator-(const Pos& t) const;
	Pos operator*(const double f) const;

public:
	Pos& operator=(const Pos& t);
	Pos& operator+=(const Pos& t);
	Pos& operator*=(const double f);

public:
	double& operator[](const unsigned int i);

public:
	void setZero();
	double length() const;
	int getDim() const;

private:
	int dim;
	std::vector<double> pos;
};

typedef std::unordered_map<Node, Pos> NodePosSet;

typedef std::pair<Node, CID> NodeCID;
typedef std::vector<NodeCID> NodeCIDSet;
