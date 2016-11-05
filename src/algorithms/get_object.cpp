#include "../models/object.h"
#include "../graph/matrix.h"
#include "../request/request.h"
#include "../models/cluster.h"
#include "../models/agent.h"
#include "numbering_graph.cpp"

using namespace std;

typedef <cluster, int> labelBlob;

int compare(labelBlob i, labelBlob j) {
    int li = get<1>i;
    int lj = get<1>j;
    if (li < lj) return (1);
    else return (0);
};

//_____________________________________________________________________________________
// Retourne les blobs triés selon le niveau de sérendipité
vector<cluster> num_s_level(int seren_level, Matrix graph, Agent a, vector<object>objects, vector<cluster>blobs) {
    vector<int> labels = number_graph(graph, a, objects, blobs);
    int n = labels.size();
    int i;
    vector<labelBlob> good_blobs; 

    for (i = 0; i < n; ++i) {
	if (labels[i] <= seren_level) {
	    good_blobs.push_back((blobs[i], labels[i]));
	};
    };

    good_blobs = sort(good_blobs.begin(), good_blobs.end(), compare);
    vector<cluster> sBlobs;
    for (i=0; i < n; ++i) {
	sBlobs.push_back(get<0>good_blobs[i]);
    };
    return(sBlobs);
};

//_____________________________________________________________________________________
// Retourne les blobs qui sont jugés pertinents par rapport à la requête @r
// dont la distance est inférieure à T_REQ
vector<cluster> sort_request(Request r, vector<cluster> sBlobs) {
    vector<cluster> ssBlobs;
    int n = sBlobs.size();
    int i;

    for (i=0; i < n; ++i) {
	if (r.d(sBlobs[i]) <= T_REQ) {
	    ssBlobs.push_back(sBlobs[i]);
	};
    };
    return (ssBlobs);
};


//_____________________________________________________________________________________
// Donne la liste d'objets associée aux Blobs sélectionnés
vector<object> get_objects(vector<cluster> sBlobs) {
    vector<object> sObjects;
    int n = sBlobs.size();
    int i;
    
    for (i = 0; i < n; ++i) {
	for (BaseCluster :: BaseIterator it = sBlobs[i].begin(); it != sBlobs[i].end(); ++it) {
	    sObjects.push_back(it);
	};
    };

    return (sObjects);
};

//_____________________________________________________________________________________
// Renvoie une liste ordonnée d'objets
vector<object> recommend(int seren_level, Matrix graph, Request r, Agent a, vector<object>objects, vector<cluster>blobs)
    vector<cluster> sBlobs = num_s_level(seren_level, graph, a, objects, blobs);
    sBlobs = sort_request(r, sBlobs);
    vector<object> sObjects = get_objects(sBlobs);

    return (sObjects);

};
