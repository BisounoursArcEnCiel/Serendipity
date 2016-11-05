#include <stdlib.h>
#include <time.h>
#include <tuple>

#include <misc/misc.h>
#include <models/object.h>

typedef tuple<vector<object>, vector<object>> sampling;

//___________________________________________________________________
// SWAPPING STEP

sampling swap(vector<object>set, vector<object>reservoir, object e, int i, int j) {
    sampling res;
    // Les names sont des identifiants uniques
    if (set[i].get_name() == e.get_name()) {
        set[i] = reservoir[j];
    };
    reservoir[j] = e;
    get<0>res = set;
    get<1>res = reservoir;
    return (res);
};

//___________________________________________________________________
// SELECTION STEP

vector<object> random_selection(vector<object>initSet, vector<object>reservoir, int k) {
    int n = initSet.size();
    if (k > n) {
        return (reservoir);
    };
    if (k == n) {
	return (initSet);
    };
    
    int i, j;
    sampling s;
    vector<object> set;

    // Initialisation du réservoir
    for(j=0; j < k; ++j) {
	reservoir.push_back(initSet[j]);
    };
    
    // Initialisation du set
    for(i=0; i < k; ++i) {
	object oo;
	set[i] = oo;
    };
    for(i=k; i < n; ++i) {
	set[i] = initSet[i];
    };

    srand (time(NULL));
    for(i=k; i < n; ++i) {
	j = rand() % i;
	if (j < k) {
	    s = swap(set, reservoir, initSet[i], i, j);
	    set = get<0>s;
	    reservoir = get<1>s;
	};
    };
    return (reservoir);
};
