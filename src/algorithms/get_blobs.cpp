#include "../models/object.h"
#include "../models/cluster.h"
#include "../misc/misc.h"
#include <config.h>

using namespace std;

// T_BLOB est la distance maximale entre deux objets d'un même blob
// @clusters est le résultat de K-MEANS
// @objects est l'ensemble des objets
vector<cluster> get_blobs(vector<cluster>clusters, vector<int>currAssign, vector<object>objects) {
    int i, j, l;
    int k = clusters.size();
    int objLen = objects.size();
    for (i = 0; i < objLen; ++i) {
	object currObj = objects[i];
	for (j = 0; j < objLen; ++j) {
	    object obj = objects[j]
	    int cond1 = !(obj.get_name() == currObj.get_name());
	    int cond2 = !(currAssign[j] == currAssign[j]);
	    int cond3 = !(obj.d(currObj) < T_BLOB);
	    if (cond1 and cond2 and cond3)) {
	         clusters[currAssign[j]].add(currObj);
	    };
	};
    };

    return (clusters);

};
