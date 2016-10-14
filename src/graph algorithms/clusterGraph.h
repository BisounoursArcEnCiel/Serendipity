#include <Cluster.h>
#include <Agent.h>
#include <graphs/matrix.h>
#include <vector.h>

Matrix get_cluster_graph(Cluster* clusters, int nb_clusters, Agent a) {
    Matrix<dcluster, dobjet> m;
    int i;
    for(i = 0; i < nb_clusters; ++i) {
	m.add(clusters[i]);
    };
    return (m);
};
