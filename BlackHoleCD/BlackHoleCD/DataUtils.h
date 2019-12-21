#pragma once

#include "type.h"

class DataUtils {
public:
	static std::string getDataRoot(const std::string& exePath);
	static std::string readNetwork(const std::string& dataRoot, const std::string& dataset, Network& network);
	static std::string writeNodePoses(const std::string& dataRoot, const std::string& dataset, const NodePosSet& nodePoses);
	static std::string writeNodeCIDs(const std::string& dataRoot, const std::string& dataset, const NodeCID& nodeCID);
	static void draw(const std::string& dataRoot, const std::string& dataset, const std::string& dataFilename, const std::string& clusterFilename, NodePosSet& nodePoses);
	static void metrics(const std::string& dataFilename, const std::string& clusterFilename);
};