import networkx as nx
import matplotlib.pyplot as plt
import sys

assert len(sys.argv) == 4

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

colors = {}
with open(sys.argv[3]) as fin:
    for line in fin:
        items = line.strip().split()[:2]
        assert len(items) == 2
        colors[int(items[0])] = int(items[1])
print(len(list(filter(lambda x: x == -2, colors.values()))))
# print(set(colors.values()))
n = len(set(colors.values()))
print(n)
colors = [(colors[x] + 2) / n for x in G.nodes()]
# colors = list(colors.items())
# colors.sort()
# colors = [x[1] + 1 / 10 for x in colors]

nx.draw(G, with_labels=False, edge_color='lightblue', pos=poses, node_color=colors, node_size=100, width=1)  #
plt.show()
