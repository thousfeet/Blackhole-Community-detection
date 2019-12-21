# datasets = ["Amazon\\amazon", "DBLP\\dblp", "Livejournal\\lj", "Orkut\\orkut", "Youtube\\youtube", "Football\\football"]
datasets = ["DBLP\\dblp"]
d = {}
c = 1
r = []
for dataset in datasets:
    with open(dataset + '.ungraph.txt') as fin:
        for line in fin:
            if line.startswith('#'):
                continue
            v1, v2 = map(int, line.split()[:2])
            r.append((v1, v2))
            if v1 not in d:
                d[v1] = c
                c += 1
            if v2 not in d:
                d[v2] = c
                c += 1
    with open(dataset + '.ungraph_convert.txt', 'w') as out:
        for v1, v2 in r:
            out.write(f'{d[v1]}\t{d[v2]}\n')
