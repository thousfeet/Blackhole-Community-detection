#pragma once
#include "DataUtils.h"


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
	double calEnergy(const Network& network, const double a, const double r, NodePosSet & poses);
	double calEnergy(const Pos& pu, const Pos& pv, const double p);
	double calAttractiveEnergy(const EdgeSet& edges, const double a, NodePosSet& poses);
	double calRepulsiveEnergy(const Network& network, const double r, NodePosSet & poses);
	void updateParam(const int iter);

private:
	const int dim;
	double a;
	double r;
	const double fa;
	const double fr;
	const int nIters;
};

