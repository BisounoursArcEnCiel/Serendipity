// Implémentation de l'algorithme de Dijkstra avec une matrice d'adjacence
// Entrée : graphe + noeud de départ + tableau
// (non initialisé) des distances + nombre de noeuds
// (le chemin le plus court en lui-même ne nous intéresse pas)

#include <utility>
#include <vector>
#include "../misc/misc.h"
#include "../graphs/matrix.h"

using namespace std;
using namespace graphs;

typedef Matrix<d_cl, d_obj> matrix_t;
typedef vector<int> VI;
typedef vector<float> VF;

int length_tab(VI Q, int n) {
    int cpt = 0;
    for(int i=0; i < n; ++i) {
	if (Q[i]) ++cpt;
    };
    return cpt;
};


int get_next(VI Q, int n, int start) {
    int i;
    for(i=start; i < n; ++i) {
	if (Q[i]) break; 
    };
    for(i=0; i < start; ++i) {
	if (Q[i]) break; 
    };
    return i;
};


int extract_min(VF distance, VI Q, int n) {
    int next = get_next(Q, n, 0);
    float min = distance[next];
    int node;
    for(int i=next; i < n; ++i) {
	next = get_next(Q, n, next);
	if (min > Q[next]) {
	    min = Q[next];
	    node = next;
	};
    };
    return node;
};


cluster_t lookforcluster(int id, vector<cluster_t*>& clusters, int n) {
    int i;
    for(i = 0; i < n; ++i) {
	if (clusters[i]->get_id() == (cluster_id_t)id) {
	    break;
	};
    };
    return clusters[i];
};


VF dijkstra(vector<cluster_t*>& clusters, matrix_t graph, int s, VF distance, int n) {
    //Initialisation du tableau des distances @distance
    int i;
    VI Q;
    for (i=0; i < n; ++i) {
	distance.push_back(INFINITY);
        Q.push_back(1);
    };
    distance[s] = 0;
    while (length_tab(Q, n)) {
	int mini = extract_min(distance, Q, n);
        Q[mini] = 0;
	cluster_t cl = lookforcluster(mini, clusters, n);
	VI neighbors = graph.get_neighbours(&cl);
	int len = neighbors.size();
	for (i=0; i < len; ++i) {
	    float temp = distance[neighbors[i]->get_id()] + 1;
	    if (temp < distance[mini]) {
		distance[mini] = temp;
	    };
	};
    };
    return distance;
};
