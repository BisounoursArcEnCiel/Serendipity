// Implémentation de l'algorithme de Dijkstra avec une matrice d'adjacence
// Entrée : graphe + noeud de départ + tableau
// (non initialisé) des distances + nombre de noeuds
// (le chemin le plus court en lui-même ne nous uint64_téresse pas)

#include <utility>
#include <vector>
#include <list>
#include "../misc/misc.h"
#include "../graphs/matrix.h"

using namespace std;
using namespace graphs;

typedef Matrix<d_cl, d_obj> matrix_t;
typedef vector<uint64_t> VI;
typedef vector<float> VF;

uint64_t length_tab(VI Q, uint64_t n) {
    uint64_t cpt = 0;
    for(uint64_t i=0; i < n; ++i) {
	if (Q[i]) ++cpt;
    };
    return cpt;
};


uint64_t get_next(VI Q, uint64_t n, uint64_t start) {
    uint64_t i;
    for(i=start; i < n; ++i) {
	if (Q[i]) break; 
    };
    for(i=0; i < start; ++i) {
	if (Q[i]) break; 
    };
    return i;
};


uint64_t extract_min(VF distance, VI Q, uint64_t n) {
    uint64_t next = get_next(Q, n, 0);
    float min = distance[next];
    uint64_t node;
    for(uint64_t i=next; i < n; ++i) {
	next = get_next(Q, n, next);
	if (min > Q[next]) {
	    min = Q[next];
	    node = next;
	};
    };
    return node;
};


cluster_t* lookforcluster(uint64_t id, vector<cluster_t*>& clusters, uint64_t n) {
    uint64_t i;
    for(i = 0; i < n; ++i) {
	if (clusters[i]->get_id() == (cluster_id_t)id) {
	    break;
	};
    };
    return clusters[i];
};


VF dijkstra(vector<cluster_t*>& clusters, matrix_t& graph, uint64_t s, VF distance, uint64_t n) {
    //Initialisation du tableau des distances @distance
    uint64_t i;
    VI Q;
    for (i=0; i < n; ++i) {
	distance.push_back(INFINITY);
        Q.push_back(1);
    };
    distance[s] = 0;
    while (length_tab(Q, n)) {
	uint64_t mini = extract_min(distance, Q, n);
        Q[mini] = 0;
	cluster_t* cl = lookforcluster(mini, clusters, n);
	list<cluster_t*> neighbors = graph.get_neighbours(cl->get_id());
	for (list<cluster_t*>::iterator it=neighbors.begin(); it!=neighbors.end(); ++it){
	    float temp = distance[(*it)->get_id()] + 1;
	    if (temp < distance[mini]) {
		distance[mini] = temp;
	    };
	};
    };
    return distance;
};
