datasets = ["Amazon\\amazon", "DBLP\\dblp", "Youtube\\youtube"]


for dataset in datasets:
    with open(dataset + '.gt.txt', 'w') as out:
        with open(dataset + '.top5000.cmty.txt') as fin:
            for i, line in enumerate(fin, start=1):
                for d in map(int, line.split()):
                    out.write(f'{d} {i}\n')
