#include "../models/cluster.h"
#include "../models/agent.h"
#include "../models/object.h"
#include "../graphs/matrix.h"
#include "dijkstra.cc"
#include "../misc/misc.h"
#include "../misc/types.h"

#include <utility>
#include <vector>

using namespace std;

typedef vector<float> VF;
typedef Matrix<d_cl, d_obj> matrix_t;

//_______________________________________________________________________
// Calcul du coefficient de connaissance de l'agent
float knowledge(agent_t a, vector<object_t*>& objects) {
    int n = objects.size();
    int s = 0;

    for (int i = 0; i < n; ++i) {
	object_id_t obj = objects[i]->get_name();
	s += a.get(obj);
    };
    
    return s/n;
};

//_______________________________________________________________________
// Détermine les centres du champ de l'agent
vector<cluster_t> get_centres(matrix_t graph, agent_t a, vector<cluster_t*>& blobs) {
    vector<cluster_t> centres;
    float maxPref = INFINITY;
    int k = blobs.size();
    int i;
    
    for (i = 0; i<k; ++i) {
	float pref = a.get(blobs[i]->get_id());
	if ((maxPref == INFINITY) or (maxPref < pref)) {
	    maxPref = pref;
	};
    };

    for (i = 0; i<k; ++i) {
	float pref = a.get(blobs[i]->get_id());
	if (maxPre == pref) {
	    centres.push_back(blobs[i]);
	};
    };

    return centres;
};

//_______________________________________________________________________
// Calcul de d_edges d'un objet par rapport aux centres

int d_edges(cluster_t blob, vector<VF> distances, vector<cluster_t*>& blobs) {
    int index = 0;
    int n = blobs.size();
    while (!(blob->get_id() == blobs[index]->get_id())) {
	++index;
    };
    
    float minDist = INFINITY;
    int n_centres = distances.size();
    int i;
    
    for (i=0; i < n_centres; ++i) {
	float dist = distances[i][index];
	if ((minDist == INFINITY) or (minDist > dist)) {
	    minDist = dist;
	};
    };

    return minDist;
};

//_______________________________________________________________________
// Almost-zero knowledge approach
vector<float> azka(matrix_t graph, agent_t a, vector<float>labels, vector<cluster_t*>& blobs) {
    vector<cluster_t*>& centres;
    centres = get_centres(graph, a, blobs, centres);
    int n_centres = centres.size();
    int n_blobs = blobs.size();
    int i;
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
vector<float> pba(matrix_t graph, agent_t a, vector<float>labels, vector<cluster_t*>& blobs) {
    vector<cluster_t*>& centres = get_centres(graph, a, blobs);
    int n_centres = centres.size();
    int n_blobs = blobs.size();
    int i, j;
    for (i = 0; i < n_centres; ++i) {
	labels[centres[i]->get_id()] = 0;
    };

    for (i = 0; i < n_blobs; ++i) {
	if (labels[blobs[i]->get_id()] == INFINITY) {
	    float minPref = INFINITY;
	    for (j = 0; j < n_centres; ++j) {
                float pref = abs(a.get(centres[j]->get_id()) - a.get(blobs[i]->get_id())); 
                if ((minPref == INFINITY) or (pref < minPref)) {
                     minPref = pref;
                };
	    };
            int currLabel = 1;
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
vector<float> number_graph(matrix_t graph, agent_t a, vector<object_t*>& objects, vector<cluster_t*>& blobs) {
    int knowl = knowledge(a, objects);
    int i;
    int n = blobs.size();
    vector<float> labels;
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
    
