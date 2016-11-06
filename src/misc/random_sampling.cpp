#include <stdlib.h>
#include <time.h>
#include <tuple>

#include "misc.h"
#include "types.h"
#include "../models/object.h"

using namespace std;
typedef pair<vector<object_t*>, vector<object_t*>> sampling;

//___________________________________________________________________
// SWAPPING STEP

sampling swap(vector<object_t*>set, vector<object_t*>reservoir, object_t* e, int i, int j) {
    sampling res;
    // Les names sont des identifiants uniques
    if (set[i]->get_name() == e->get_name()) {
        set[i] = reservoir[j];
    };
    reservoir[j] = e;
    res.first = set;
    res.second = reservoir;
    return res;
};

//___________________________________________________________________
// SELECTION STEP

vector<object_t*> random_selection(vector<object_t*>initSet, vector<object_t*>reservoir, int k) {
    int n = initSet.size();
    if (k > n) {
        return reservoir;
    }
    if (k == n) {
    	return initSet;
    }
    
    int i, j;
    sampling s;
    vector<object_t*> set;

    // Initialisation du réservoir
    for(j=0; j < k; ++j) {
	    reservoir.push_back(initSet[j]);
    }
    
    // Initialisation du set
    for(i=0; i < k; ++i) {
	    set[i] = NULL;
    }

    for(i=k; i < n; ++i) {
	    set[i] = initSet[i];
    }

    srand (time(NULL));
    for(i=k; i < n; ++i) {
	j = rand() % i;
	if (j < k) {
	    s = swap(set, reservoir, initSet[i], i, j);
	    set = s.first;
	    reservoir = s.second;
	};
    };
    return (reservoir);
};
