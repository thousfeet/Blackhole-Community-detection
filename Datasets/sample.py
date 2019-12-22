datasets = ["Amazon\\amazon", "DBLP\\dblp", "Livejournal\\lj", "Orkut\\orkut", "Youtube\\youtube", "Football\\football"]
# datasets = ["Youtube\\youtube"]
for dataset in datasets:
    d = {}
    c = 1
    r = []
    gids = set()
    with open(dataset + '.top5000.cmty.txt') as fin:
        for line in fin:
            for _id in map(int, line.split()):
                gids.add(_id)
    with open(dataset + '.ungraph_sample.txt', 'w') as out:
        with open(dataset + '.ungraph.txt') as fin:
            for line in fin:
                if line.startswith('#'):
                    continue
                v1, v2 = map(int, line.split()[:2])
                if v1 not in gids or v2 not in gids:
                    continue
                out.write(line)
                r.append((v1, v2))
                if v1 not in d:
                    d[v1] = c
                    c += 1
                if v2 not in d:
                    d[v2] = c
                    c += 1
    with open(dataset + '.ungraph_sample_convert.txt', 'w') as out_convert:
        for v1, v2 in r:
            out_convert.write(f'{d[v1]}\t{d[v2]}\n')
    print(f'[{dataset}] nodes = {len(gids)}, edges = {len(r)}')
