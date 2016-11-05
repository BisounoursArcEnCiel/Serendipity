#include <models/cluster.h>
#include <models/agent.h>
#include <graphs/matrix.h>

Matrix get_cluster_graph(cluster* clusters, int nb_clusters, agent a) {
    Matrix<dcluster, dobjet> m;
    int i;
    for(i = 0; i < nb_clusters; ++i) {
	m.add(clusters[i]);
    };
    return (m);
};
