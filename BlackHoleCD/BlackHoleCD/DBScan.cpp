#include "DBScan.h"
#include <iostream>


NodeCIDSet DBScan::dbscan(NodePosSet& nodePoses, const float eps, const int minPts)
{
    DataUtils::writeNodePoses(".\\", "test", nodePoses);
    return NodeCIDSet();
}


