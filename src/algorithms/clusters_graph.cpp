#include "../models/cluster.h"
#include "../models/agent.h"
#include "../graphs/matrix.h"
#include "../misc/types.h"


using namespace std;
using namespace graphs;

// @k est le nombre de clusters
Matrix<d_cl, d_obj> get_clustersGraph(vector<cluster_t*>& clusters, int k) {
    Matrix<d_cl, d_obj> m;
    int i;
    for(i = 0; i < k; ++i) {
	m.add(clusters[i]);
    };
    return m;
};
