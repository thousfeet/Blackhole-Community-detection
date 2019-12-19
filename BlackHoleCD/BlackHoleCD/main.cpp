#include <iostream>
#include "BlackHole.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "WARNING: srand(1) For Debug!" << endl;
	srand(2);

	const string dataRoot = DataUtils::getDataRoot(argv[0]);
	// const vector<string> datasets = { "Amazon\\amazon", "DBLP\\dblp", "Livejournal\\lj", "Orkut\\orkut", "Youtube\\youtube", "Football\\football" };
	const vector<string> datasets = { "Football\\football" };
	const int dim = 2;
	for (const string& dataset : datasets) {
		NodeSet nodes;
		EdgeSet edges;
		DataUtils::readNetwork(dataRoot, dataset, nodes, edges);
		NodeCIDSet nodeCIDs;
		BlackHole::exec(nodes, edges, dim, nodeCIDs);
		DataUtils::writeNodeCIDs(dataRoot, dataset, nodeCIDs);
	}
	return 0;
}
