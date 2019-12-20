import networkx as nx
import matplotlib.pyplot as plt
import sys

assert len(sys.argv) == 3

G = nx.Graph()
with open(sys.argv[1]) as fin:
    edges = []
    for line in fin:
        if line.startswith('#'):
            continue
        G.add_edge(*map(int, line.split()))
poses = {}
with open(sys.argv[2]) as fin:
    for line in fin:
        items = line.strip().split()
        assert len(items) == 3
        poses[int(items[0])] = tuple(float(x) for x in items[1:])
nx.draw(G, with_labels=False, edge_color='b', pos=poses, node_color='r', node_size=10, width=1)
plt.show()
