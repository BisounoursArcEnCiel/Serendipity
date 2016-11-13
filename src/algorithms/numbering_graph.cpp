#include "../models/cluster.h"
#include "../models/agent.h"
#include "../models/object.h"
#include "../graphs/matrix.h"
#include "dijkstra.cc"
#include "../misc/misc.h"
#include "../misc/types.h"

#include <utility>
#include <vector>
#include <cmath>

using namespace std;
using namespace graphs;
typedef vector<float> VF;
typedef Matrix<d_cl, d_obj> matrix_t;
typedef pair<uint64_t, uint64_t> PII;
typedef vector<pair<uint64_t, uint64_t>> VPII;
typedef vector<uint64_t> VI;

//_______________________________________________________________________
// Calcul du coefficient de connaissance de l'agent
float knowledge(agent_t& a, vector<object_t*>& objects) {
    uint64_t n = objects.size();
    uint64_t s = 0;
    uint64_t i;

    for (i = 0; i < n; ++i) {
        models::object_id_t obj = objects[i]->get_name();
	s += a.get(obj);
    };
    
    return s/n;
};

//_______________________________________________________________________
// Détermine les centres du champ de l'agent
vector<cluster_t*> get_centres(matrix_t& graph, agent_t& a, vector<cluster_t*>& blobs) {
    vector<cluster_t> centres;
    float maxPref = INFINITY;
    uint64_t k = blobs.size();
    uint64_t i;
    
    for (i = 0; i<k; ++i) {
        float pref = a.get(blobs[i]->get_id());
	if ((maxPref == INFINITY) or (maxPref < pref)) {
	        maxPref = pref;
	};
    };

    for (i = 0; i<k; ++i) {
	float pref = a.get(blobs[i]->get_id());
    	if (maxPref == pref) {
	        centres.push_back(blobs[i]);
    	};
    };

    return (centres);
};

//_______________________________________________________________________
// Calcul de d_edges d'un objet par rapport aux centres

uint64_t d_edges(cluster_t* blob, vector<VI>& distances, vector<cluster_t*>& blobs) {
    uint64_t index = 0;
    while (!(blob->get_id() == blobs[index]->get_id())) {
	    ++index;
    };
    
    float minDist = INFINITY;
    uint64_t n_centres = distances.size();
    
    for (uint64_t i=0; i < n_centres; ++i) {
        float dist = distances[i][index];
        if ((minDist == INFINITY) or (minDist > dist)) {
            minDist = dist;
        };
    };

    return minDist;
};

//_______________________________________________________________________
// Almost-zero knowledge approach
vector<uint64_t> azka(Matrix<d_cl,d_obj> graph, agent_t& a, vector<uint64_t>& labels, vector<cluster_t*>& blobs) {
    vector<cluster_t*>centres;
    centres = get_centres(graph, a, blobs, centres);
    uint64_t n_centres = centres.size();
    uint64_t n_blobs = blobs.size();
    uint64_t i;
    VPII edges = convert(graph, n_blobs);
    vector<VF> distances;
    for (i = 0; i < n_centres; ++i) {
	labels[centres[i]->get_id()] = 0;
	VF distance;
	distances.push_back(dijkstra(graph, centres[i]->get_id(), distance, n_blobs));
    };

    for (i = 0; i < n_blobs; ++i) {
	if (labels[blobs[i]->get_id()] == INFINITY) {
	    labels[blobs[i]->get_id()] = d_edges(blobs[i], distances, blobs);
	};
    };

    return labels;
};

//_______________________________________________________________________
// Preference-based approach
// T_LEVEL défini dans misc.h est la largeur du niveau de sérendipité
vector<uint64_t> pba(Matrix<d_cl,d_obj>& graph, agent_t& a, vector<uint64_t>labels, vector<cluster_t*>blobs) {
    vector<cluster_t*>centres;
    centres = get_centres(graph, a, blobs, centres);
    uint64_t n_centres = centres.size();
    uint64_t n_blobs = blobs.size();
    uint64_t i, j;
    for (i = 0; i < n_centres; ++i) {
	    labels[centres[i]->get_id()] = 0;
    };

    for (i = 0; i < n_blobs; ++i) {
        if (labels[blobs[i]->get_id()] == INFINITY) {
            float minPref = INFINITY;
            for (j = 0; j < n_centres; ++j) {
                    float pref = fabs(a.get(centres[j]->get_id()) - a.get(blobs[i]->get_id())); 
                    if ((minPref == INFINITY) or (pref < minPref)) {
                         minPref = pref;
                    };
            };
                uint64_t currLabel = 1;
                while (minPref > currLabel*T_LEVEL) {
                      ++currLabel;
                };
            labels[blobs[i]->get_id()] = currLabel;
        };
    };

    return labels;
};

//_______________________________________________________________________
// Numérotation du Blobs graph
// @objects est l'ensemble des objets dans le graphe
// @blobs est l'ensemble des blobs dans le graphe
vector<uint64_t> number_graph(Matrix<d_cl, d_obj>& graph, agent_t& a, vector<object_t*>objects, vector<cluster_t*>blobs) {
    uint64_t knowl = knowledge(a, objects);
    uint64_t i;
    uint64_t n = blobs.size();
    vector<uint64_t> labels;
    for(i = 0; i < n; ++i) {
	    labels.push_back(INFINITY);
    };

    if (knowl > T_KNOW) {
	    // Preference-based approach
	    labels = pba(graph, a, labels, blobs);
    }
    else {
	    //Almost-zero knowledge approach
	    labels = azka(graph, a, labels, blobs);
    };

    return labels;
};

