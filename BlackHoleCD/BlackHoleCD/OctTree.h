#pragma once

#include "DataUtils.h"
#include <unordered_map>


class OctTree
{
public:
	OctTree(const int dim, const std::unordered_map<Node, Pos>& nodes);
};

