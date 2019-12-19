#pragma once
#include "DataUtils.h"


class GraphDrawing
{
public:
	static void exec(const NodeSet& nodes, const EdgeSet& edges, const int dim, const double a, const double r, NodePosSet& nodePoses);

private:
	static Pos getRandomPos(const int dim);
	static void calAttractiveForce(const int dim, const Pos& u, const Pos& v, const double a, Pos& fa);
	static void calRepulsiveForce(const int dim, const Pos& u, const Pos& v, const double r, Pos& fr);
	static double calEnergy(const NodeSet& nodes, const EdgeSet& edges, const int dim, const double a, const double r, NodePosSet & poses);
	static double calEnergy(const Pos& pu, const Pos& pv, const double p);
	static double calAttractiveEnergy(const EdgeSet& edges, const int dim, const double a, NodePosSet& poses);
	static double calRepulsiveEnergy(const NodeSet& nodes, const int dim, const double r, NodePosSet & poses);
};

