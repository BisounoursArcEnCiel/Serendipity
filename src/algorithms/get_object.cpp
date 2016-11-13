#include "../models/object.h"
#include "../graphs/matrix.h"
#include "../request/request.h"
#include "../models/cluster.h"
#include "../models/agent.h"
#include "../misc/types.h"
#include "../request/request.h"
#include "numbering_graph.cpp"

#include <utility>

using namespace std;

typedef pair<cluster_t*, uint64_t> labelBlob;

uint64_t compare(labelBlob& i, labelBlob& j) {
    uint64_t li = i.second;
    uint64_t lj = j.second;
    if (li < lj) return (1);
    else return (0);
};

//_____________________________________________________________________________________
// Retourne les blobs triés selon le niveau de sérendipité
vector<cluster_t*> num_s_level(uint64_t seren_level, Matrix<d_cl, d_obj>& graph, agent_t& a, vector<object_t*>objects, vector<cluster_t*>&blobs) {
    vector<uint64_t> labels = number_graph(graph, a, objects, blobs);
    uint64_t n = labels.size();
    uint64_t i;
    vector<labelBlob> good_blobs; 

    for (i = 0; i < n; ++i) {
	if (labels[i] <= seren_level) {
	    good_blobs.push_back((blobs[i], labels[i]));
	};
    };

    good_blobs = sort(good_blobs.begin(), good_blobs.end(), compare);
    vector<cluster_t*> sBlobs;
    for (i=0; i < n; ++i) {
	    sBlobs.push_back(good_blobs[i].first);
    };
    return(sBlobs);
};

//_____________________________________________________________________________________
// Retourne les blobs qui sont jugés pertinents par rapport à la requête @r
// dont la distance est inférieure à T_REQ
vector<cluster_t*> sort_request(request::Request& r, vector<cluster_t*>& sBlobs) {
    vector<cluster_t*> ssBlobs;
    uint64_t n = sBlobs.size();
    uint64_t i;

    for (i=0; i < n; ++i) {
	if (r.d(sBlobs[i]) <= T_REQ) {
	    ssBlobs.push_back(sBlobs[i]);
	};
    };
    return (ssBlobs);
};


//_____________________________________________________________________________________
// Donne la liste d'objets associée aux Blobs sélectionnés
vector<object> get_objects(vector<cluster_t*>& sBlobs) {
    vector<object_t*> sObjects;
    uint64_t n = sBlobs.size();
    uint64_t i;
    
    for (i = 0; i < n; ++i) {
	for (BaseCluster :: BaseIterator it = sBlobs[i].begin(); it != sBlobs[i].end(); ++it) {
	    sObjects.push_back(it);
	};
    };

    return (sObjects);
};

//_____________________________________________________________________________________
// Renvoie une liste ordonnée d'objets
vector<object> recommend(uint64_t seren_level, Matrix<d_cl,d_obj>& graph, Reques&t r, agent_t& a, vector<object_t*>& objects, vector<cluster_t*>&blobs)
    vector<cluster> sBlobs = num_s_level(seren_level, graph, a, objects, blobs);
    sBlobs = sort_request(r, sBlobs);
    vector<object> sObjects = get_objects(sBlobs);

    return (sObjects);

};
