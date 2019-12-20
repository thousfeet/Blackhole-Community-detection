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
ClusterSet - unordered_map: <CID, NodeSet>

Pos - vector: {<double>} 节点在空间中的位置
NodePosSet - unordered_map: <Node, Pos>

NodeCID - unordered_map: <Node, CID> 节点所属的cluster
NodeNearPoints - unordered_map: <Node, NodeSet>
***********************************************/

typedef unsigned int Node;
typedef std::unordered_set<Node> NodeSet;

typedef unsigned long long Edge;
typedef std::unordered_set<Edge> EdgeSet;

typedef unsigned int CID;
typedef std::unordered_map<CID, NodeSet> ClusterSet;

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
	double eucDis() {
		double euc = 0;
		for (int i = 0; i < dim; i++) {
			euc += pos[i] * pos[i];
		}
		return euc;
	}

private:
	int dim;
	std::vector<double> pos;
};

typedef std::unordered_map<Node, Pos> NodePosSet;
typedef std::unordered_map<Node, NodeSet> NodeNearPoints;
typedef std::unordered_map<Node, CID> NodeCID;