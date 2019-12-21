#pragma once
#include "DataUtils.h"
#include "OctTree.h"


class GraphDrawing
{
public:
	GraphDrawing(const int dim, const double a, const double r, int nIters);

public:
	void exec(const Network& network, NodePosSet& nodePoses);

private:
	Pos getRandomPos();
	void calAttractiveForce(const Pos& u, const Pos& v, const double a, Pos& fa);
	void calRepulsiveForce(const Pos& u, const Pos& v, const double r, Pos& fr);
	void calRepulsiveForce(const Pos& u, OctTree* tree, const double r, Pos& fr);
	double calEnergy(const Network& network, const double a, const double r, NodePosSet & poses);
	double calEnergy(const Network& network, OctTree* tree, const double a, const double r, NodePosSet & poses);
	double calEnergy(const Pos& pu, const Pos& pv, const double p);
	double calEnergy(const Pos& pu, OctTree* tree, const double p);
	double calAttractiveEnergy(const EdgeSet& edges, const double a, NodePosSet& nodePoses);
	double calRepulsiveEnergy(const Network& network, const double r, NodePosSet & nodePoses);
	double calRepulsiveEnergy(const Network& network, OctTree* tree, const double r, NodePosSet & nodePoses);
	void updateParam(const int iter);

private:
	const int dim;
	double a;
	double r;
	const double fa;
	const double fr;
	const int nIters;
};

