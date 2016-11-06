#include "../models/cluster.h"
#include "../models/agent.h"
#include "../graphs/matrix.h"
#include "../distances/cluster2cluster.h"
#include "../distances/obj2obj.h"

using namespace std;

// @k est le nombre de clusters
Matrix get_clustersGraph(vector<cluster>clusters, int k, agent a) {
    Matrix<cl2cl, obj2obj> m;
    int i;
    for(i = 0; i < k; ++i) {
	m.add(clusters[i]);
    };
    return (m);
};
