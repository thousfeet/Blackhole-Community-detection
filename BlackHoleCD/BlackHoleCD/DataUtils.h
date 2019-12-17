#pragma once

#include "type.h"


#define EDGE(v1, v2) (v1 < v2 ? ((Edge(v1) << 32) | v2) : ((Edge(v2) << 32) | v1))


class DataUtils {
public:
	static std::string getDataRoot(const std::string& exePath);
	static void readNetwork(const std::string& dataRoot, const std::string& dataset, NodeSet& nodes, EdgeSet &edges);
	static void writeNodeCIDs(const std::string& dataRoot, const std::string& dataset, const NodeCIDSet& nodeCIDs);
};