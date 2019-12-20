#pragma once

#include "type.h"


class DataUtils {
public:
	static std::string getDataRoot(const std::string& exePath);
	static void readNetwork(const std::string& dataRoot, const std::string& dataset, Network& network);
	static void writeNodePoses(const std::string& dataRoot, const std::string& dataset, NodePosSet& nodePoses);
	static void writeNodeCIDs(const std::string& dataRoot, const std::string& dataset, const NodeCIDSet& nodeCIDs);
};