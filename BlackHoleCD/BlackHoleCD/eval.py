import sys

# D:\THU\现代数据库系统概论\Project2\Blackhole-Community-detection\Datasets\Football\football.nodeCIDs.txt
# D:\THU\现代数据库系统概论\Project2\BlackHoleOrigin\BlackHoleOrigin\Data\football.dat_dimsnsion_2_alpha_0.01_minPts_5_pruningFactor_0.1_position.out_MinPts_5_RemovePercent_0.1_EPS_0.149085.dat

assert len(sys.argv) == 2


clusters = {}
with open(sys.argv[1]) as fin:
    for line in fin:
        nid, cid = map(int, line.split()[:2])
        d = clusters.get(cid, [])
        d.append(nid)
        clusters[cid] = d
clusters = list(clusters.values())
for cluster in clusters:
    cluster.sort()
clusters.sort(key=lambda x: x[0])
for nid_cluster in clusters:
    print(', '.join(map(str, nid_cluster)))
