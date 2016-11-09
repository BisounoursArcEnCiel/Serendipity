#include "../models/cluster.h"
#include "../models/agent.h"
#include "../models/object.h"
#include "../graphs/matrix.h"
#include "FastDijkstra.cc"
#include "../misc/misc.h"

#include <utility>

using namespace std;

typedef pair<int, int> PII;
typedef vector<pair<int, int>> VPII;
typedef vector<int> VI;

//_______________________________________________________________________
// Calcul du coefficient de connaissance de l'agent
float knowledge(agent a, vector<object>objects) {
    int n = objects.size();
    int s = 0;
    int i;

    for (i = 0; i < n; ++i) {
	object_id_t obj = objects[i].get_name();
	s += a.get(obj);
    };
    
    return (s/n);
};

//_______________________________________________________________________
// Détermine les centres du champ de l'agent
vector<cluster> get_centres(Matrix graph, agent a, vector<cluster>blobs, vector<cluster>centres) {
    float maxPref = INFINITY;
    int k = blobs.size();
    int i;
    
    for (i = 0; i<k; ++i) {
	float pref = a.get(blobs[i].get_id());
	if ((maxPref == INFINITY) or (maxPref < pref)) {
	    maxPref = pref;
	};
    };

    for (i = 0; i<k; ++i) {
	float pref = a.get(blobs[i].get_id());
	if (maxPre == pref) {
	    centres.push_back(blobs[i]);
	};
    };

    return (centres);
};

//_______________________________________________________________________
// Convertir Matrix en VPII pour utiliser Dijkstra
VPII convert(Matrix graph, int k) {
    VPII edges;
    int i, j;

    for (i=0; i < k; ++i) {
	for (j=0; j < k; ++j) {
	    double edge = graph.get(i, j);
	    if (edge) {
		edges.push_back(PII (i, j));
	    };
	};
    };
    
    return (edges);
};

//_______________________________________________________________________
// Calcul de d_edges d'un objet par rapport aux centres

int d_edges(cluster blob, vector<VI> distances, vector<cluster>blobs) {
    int index = 0;
    int n = blobs.size();
    while (!(blob.get_id() == blobs[index].get_id())) {
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

    return(minDist);
};

//_______________________________________________________________________
// Almost-zero knowledge approach
vector<int> azka(Matrix graph, agent a, vector<int>labels, vector<cluster>blobs) {
    vector<cluster>centres;
    centres = get_centres(graph, a, blobs, centres);
    int n_centres = centres.size();
    int n_blobs = blobs.size();
    int i;
    VPII edges = convert(graph, n_blobs);
    vector<VI> distances;
    for (i = 0; i < n_centres; ++i) {
	labels[centres[i].get_id()] = 0;
	distances.push_back(Dijkstra(edges, centres[i]));
    };

    for (i = 0; i < n_blobs; ++i) {
	if (labels[blobs[i]] == INFINITY) {
	    labels[blobs[i]] = d_edges(blobs[i], distances, blobs);
	};
    };

    return (labels);
};

//_______________________________________________________________________
// Preference-based approach
// T_LEVEL défini dans misc.h est la largeur du niveau de sérendipité
vector<int> pba(Matrix graph, agent a, vector<int>labels, vector<cluster>blobs) {
    vector<cluster>centres;
    centres = get_centres(graph, a, blobs, centres);
    int n_centres = centres.size();
    int n_blobs = blobs.size();
    int i, j;
    for (i = 0; i < n_centres; ++i) {
	labels[centres[i].get_id()] = 0;
    };

    for (i = 0; i < n_blobs; ++i) {
	if (labels[blobs[i]] == INFINITY) {
	    float minPref = INFINITY;
	    for (j = 0; j < n_centres; ++j) {
                float pref = abs(a.get(centres[j]) - a.get(blobs[i])); 
                if ((minPref == INFINITY) or (pref < minPref)) {
                     minPref = pref;
                };
	    };
            int currLabel = 1;
            while (minPref > currLabel*T_LEVEL) {
                  ++currLabel;
            };
	    labels[blobs[i]] = currLabel;
	};
    };

    return (labels);
};

//_______________________________________________________________________
// Numérotation du Blobs graph
// @objects est l'ensemble des objets dans le graphe
// @blobs est l'ensemble des blobs dans le graphe
vector<int> number_graph(Matrix graph, agent a, vector<object>objects, vector<cluster>blobs) {
    int knowl = knowledge(a, objects);
    int i;
    int n = blobs.size();
    vector<int> labels;
    for(i = 0; i < n; ++i) {
	labels.push_back(INFINITY)
    };

    if (knowl > T_KNOW) {
	// Preference-based approach
	labels = pba(graph, a, labels, blobs);
    }
    else {
	//Almost-zero knowledge approach
	labels = azka(graph, a, labels, blobs);
    };

    return(labels);
};
    
