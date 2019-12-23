from collections import defaultdict
import numpy as np

import networkx as nx
import matplotlib.pyplot as plt
import sys

dataFilePath = sys.argv[1]
clusterFilePath = sys.argv[2]


########## debug football authors
rootPath = "D:/Blackhole-Community-detection/Datasets/Football/"
dataFilePath = rootPath + "football.ungraph.txt"
clusterFilePath = rootPath + "outputfile.dat"

########## debug football ours
# rootPath = "../../Datasets/Football/"
# dataFilePath = rootPath + "football.ungraph.txt"
# clusterFilePath = rootPath + "football.nodeCIDs.txt"

########## debug Amazon authors
# rootPath = "D:/Blackhole-Community-detection/Datasets/Amazon/"
# dataFilePath = rootPath + "amazon.ungraph_sample_convert.txt"
# clusterFilePath = rootPath + "amazon.dat"

########## debug Amazon ours
# rootPath = "D:/Blackhole-Community-detection/Datasets/Amazon/"
# dataFilePath = rootPath + "amazon.ungraph_sample.txt"
# clusterFilePath = rootPath + "amazon.nodeCIDs.txt"

########## debug DBLP authors
# rootPath = "D:/Blackhole-Community-detection/Datasets/DBLP/"
# dataFilePath = rootPath + "dblp.ungraph_sample_convert.txt"
# clusterFilePath = rootPath + "dblp.ungraph_sample_convert.txt_dimsnsion_2_alpha_0.01_minPts_5_pruningFactor_0.1_position.out_MinPts_5_RemovePercent_0.1_EPS_1.30167.dat"

########## debug youtube authors
rootPath = "D:/Blackhole-Community-detection/Datasets/Youtube/"
dataFilePath = rootPath + "youtube.ungraph.txt"
clusterFilePath = rootPath + "youtube.dat"


########
# internal density (M1), ms / (ns*(ns-1)/2) ↑
# edges inside(M2), ms ↑
# average degree (M3), 2*ms / ns ↑
# fraction over median degree (M4), |指向社区内的边数>社区内所有节点边数中位数 的节点|/ns  ↑
# expansion (M5), cs/ns ↓
# cut ratio (M6),  cs / ns*(n-ns) ↓
# conductance (M7), cs / (2*ms+cs) ↓
# normalized cut (M8), M7 + cs / (2*(m-ms)+cs) ↓
# flake out degree fraction (M9), |指向社区内的边数<指向社区外的边数 的节点|/ns ↓

# 整张图的总边数m、节点数n
# 一个社区的内部边数ms、节点数ns
# cs = 社区内节点指向社区外的边数和
# 一个节点的度数d、指向社区内社区外的度数
########

def M1(ms, ns):
    return ms / (ns * (ns - 1) / 2)


def M2(ms):
    return ms


def M3(ms, ns):
    return 2 * ms / ns


def M4(node_di, node_edge, ns):
    edges = []
    for node in node_di:
        edges.append(int(node_edge[node]))
    mid = np.median(np.array(edges))
    # print("mid", mid)
    cnt = 0
    for node in node_di:
        if node_di[node] > mid: cnt += 1
    # print(node_di)
    # print("cnt",cnt)
    return cnt / ns


def M5(cs, ns):
    return cs / ns


def M6(cs, n, ns):
    return cs / ns * (n - ns)


def M7(cs, ms):
    return cs / (2 * ms + cs)


def M8(cs, m, ms):
    return M7(cs, ms) + cs / (2 * (m - ms) + cs)


def M9(node_di, node_edge):
    cnt = 0
    for node in node_di:
        if node_di[node] < node_edge[node] / 2: cnt += 1
    return cnt / ns


#############################################
# node_node dict{node, {相邻node}}
# node_CID dict{node, CID}
# CID_node dict{CID, {nodes}}
# node_edge dict{node, 度数}
# node_di dict{node, 指向cluster内的边数} （对于某cluster）
#############################################


m = 0
node_node = defaultdict(set)

with open(dataFilePath) as dataFile:
    for line in dataFile:
        if line.startswith('#'):
            continue
        m += 1
        u, v = line.split()[:2]
        node_node[u].add(v)
        node_node[v].add(u)

n = len(node_node)
node_edge = dict()
for node in node_node:
    node_edge[node] = len(node_node[node])

node_CID = dict()
CID_node = defaultdict(set)
with open(clusterFilePath) as clusterFile:
    for line in clusterFile:
        if line.startswith('#'):
            continue
        node, cid = line.split()[:2]
        node_CID[node] = cid
        if int(cid) >= 0:
            CID_node[cid].add(node)

node_di = dict()
# print("cluster", len(CID_node))

print("---------------------------------------------------------------------")
metric_tot = []
for cluster in CID_node:
    edge_cnt = 0  # 社区内所有节点的度数和
    node_di.clear()
    nodes = CID_node[cluster]
    ns = len(nodes)
    for u in nodes:
        vs = node_node[u]  # u节点的相邻节点set
        edge_cnt += len(vs)
        for v in vs:
            if v in nodes:
                if u not in node_di:
                    node_di[u] = 1
                else:
                    node_di[u] += 1
    ms = sum(map(int, node_di.values())) / 2
    cs = edge_cnt - sum(map(int, node_di.values()))
    # print("node_node", node_node)
    # print("node_di", node_di)

    # tmp = 0
    # for node in node_di:
    #     tmp += len(node_node[node])-node_di[node]
    # print("tmp", tmp)

    # print("CID", cluster)
    # print("edge_cnt", edge_cnt, "ns", ns, "ms", ms, "cs", cs)
    metric = [M1(ms, ns), M2(ms), M3(ms, ns), M4(node_di, node_edge, ns), M5(cs, ns),
              M6(cs, n, ns), M7(cs, ms), M8(cs, m, ms), M9(node_di, node_edge)]
    # print(metric)
    metric_tot.append(metric)

print("---------------------------------------------------------------------")
print("average:", np.average(metric_tot, axis=0))
