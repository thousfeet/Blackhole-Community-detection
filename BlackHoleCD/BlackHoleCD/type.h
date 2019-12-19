#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

typedef unsigned int Node;
/********************************************
����˵��

Node - int: �ڵ�ID
NodeSet - unordered_set: Node����

Edge - long long: ��Ȩ
EdgeSet - unordered_set: Edge����

CID - int: Cluster��ID
Cluster - vector: Cluster��ID����
ClusterSet - vector: Cluster���ϣ�

Pos - vector: {<double>} �ڵ��ڿռ��е�λ��
NodePos - pair: <�ڵ㣬Pos>
NodePosSet - vector: NodePos����

NodeCID - pair: <�ڵ�, ������Cluster>
NodeCIDSet - vector: NodeCID����
***********************************************/


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
