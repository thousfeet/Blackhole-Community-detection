#include <iostream>
#include <fstream>
#include <ctime>
#include "DataUtils.h"

using namespace std;

string DataUtils::getDataRoot(const string & exePath)
{
	cout << "===================================" << endl;
	cout << "\"getDataRoot\" a developing function!" << endl;
	cout << "===================================" << endl;
	return exePath.substr(0, exePath.find("BlackHoleCD")) + "Datasets\\";
}

void DataUtils::readNetwork(const string& dataRoot, const string& dataset, NodeSet& nodes, EdgeSet& edges)
{
	clock_t start = clock();
	nodes.clear();
	edges.clear();
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
		nodes.insert(v1);
		nodes.insert(v2);
		edges.insert(EDGE(v1, v2));
	}
	fin.close();
	clock_t end = clock();
	cout << "[readNetwork] [" + dataset + "] [" << double(end - start) / CLOCKS_PER_SEC << "s] " << nodes.size() << " nodes, " << edges.size() << " edges" << endl;
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
	for (const NodeCID& nodeCID : nodeCIDs)
		fout << nodeCID.first << '\t' << nodeCID.second << endl;
	fout.close();
	clock_t end = clock();
	cout << "[writeNodeCIDs] [" + dataset + "] [" << double(end - start) / CLOCKS_PER_SEC << "s] " << nodeCIDs.size() << " nodeCIDs" << endl;
}
