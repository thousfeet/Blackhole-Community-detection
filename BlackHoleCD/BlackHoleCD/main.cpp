#include <iostream>
#include <ctime>
#include "BlackHole.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "WARNING: srand(1) For Debug!" << endl;
	srand(2);

	const string dataRoot = DataUtils::getDataRoot(argv[0]);
	// const vector<string> datasets = { "Amazon\\amazon", "DBLP\\dblp", "Livejournal\\lj", "Orkut\\orkut", "Youtube\\youtube", "Football\\football" };
	const vector<string> datasets = { "Football\\football"  };
	// const vector<string> datasets = { "DBLP\\dblp"  };
	const int dim = 2;
	for (const string& dataset : datasets) {
		clock_t start = clock();
		Network network;
		string dataFilename = DataUtils::readNetwork(dataRoot, dataset, network);
		NodePosSet nodePoses;
		NodeCID nodeCID;
		BlackHole::exec(network, dim, nodePoses, nodeCID);
		string clusterFilename = DataUtils::writeNodeCIDs(dataRoot, dataset, nodeCID);
		clock_t end = clock();
		cout << "[main] [" << dataset << "] [" << double(end - start) / CLOCKS_PER_SEC << "s]" << endl;
		DataUtils::draw(dataRoot, dataset, dataFilename, clusterFilename, nodePoses);
		DataUtils::metrics(dataFilename, clusterFilename);
	}
	return 0;
}
