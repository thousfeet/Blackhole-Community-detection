#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "DataUtils.h"

using namespace std;

string DataUtils::getDataRoot(const string& exePath)
{
	cout << "WARNING: \"getDataRoot\" is a now debugging function!" << endl;
	return exePath.substr(0, exePath.find("BlackHoleCD")) + "Datasets\\";
}

void DataUtils::readNetwork(const string& dataRoot, const string& dataset, Network& network)
{
	clock_t start = clock();
	network.clear();
	string filename = dataRoot + dataset + ".ungraph.txt";
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "ERROR: Unable to read \"" + filename + "\"!" << endl;
		return;
	}
	while (fin) {
		string line;
		getline(fin, line);
		if (line.size() == 0 || line[0] == '#')
			continue;
		int p = (int)line.find('\t');
		if (p == -1)
			p = (int)line.find(' ');
		if (p == -1) {
			cout << "ERROR: Read \"" + filename + "\" failed. Error format!" << endl;
			return;
		}
		Node v1 = stoi(line.substr(0, p));
		Node v2 = stoi(line.substr(p + 1));
		
		network.insertEdge(v1, v2);
	}
	fin.close();
	clock_t end = clock();
	cout << "[readNetwork] [" + dataset + "] [" << double(end - start) / CLOCKS_PER_SEC << "s] " << network.getNodeNum() << " nodes, " << network.getEdgeNum() << " edges" << endl;
}

void DataUtils::writeNodePoses(const std::string& dataRoot, const std::string& dataset, const NodePosSet& nodePoses)
{
	clock_t start = clock();
	string filename = dataRoot + dataset + ".nodePoses.txt";
	ofstream fout(filename);
	if (!fout.is_open()) {
		cout << "ERROR: Unable to write \"" + filename + "\"!" << endl;
		return;
	}
	vector<pair<Node, Pos>> nps(nodePoses.begin(), nodePoses.end());
	sort(nps.begin(), nps.end(), [](const pair<Node, Pos>& a, const pair<Node, Pos>& b) { return a.first < b.first; });
	for (auto& np : nps) {
		fout << np.first;
		int dim = np.second.getDim();
		for (int i = 0; i < dim; ++i)
			fout << '\t' << np.second[i];
		fout << endl;
	}
	fout.close();
	clock_t end = clock();
	cout << "[writeNodeCIDs] [" << dataset << "] [" << double(end - start) / CLOCKS_PER_SEC << "s] " << nodePoses.size() << " nodePoses" << endl;
}

void DataUtils::writeNodeCIDs(const std::string& dataRoot, const std::string& dataset, const NodeCIDSet& nodeCIDs)
{
	clock_t start = clock();
	string filename = dataRoot + dataset + ".nodeCIDs.txt";
	ofstream fout(filename);
	if (!fout.is_open()) {
		cout << "ERROR: Unable to write \"" + filename + "\"!" << endl;
		return;
	}
	for (const NodeCID& nodeCIDMap : nodeCIDs) {
		for (const auto& nodeCID : nodeCIDMap)
			fout << nodeCID.first << '\t' << nodeCID.second << endl;
	}
	fout.close();
	clock_t end = clock();
	cout << "[writeNodeCIDs] [" << dataset << "] [" << double(end - start) / CLOCKS_PER_SEC << "s] " << nodeCIDs.size() << " nodeCIDs" << endl;
}
