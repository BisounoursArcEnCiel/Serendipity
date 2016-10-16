#include <models/object.h>
#include <models/cluster.h>
#include <misc/random_sampling.h>
#include <misc/misc.h>
#include <config.h>


int* update_assign(int* currentAssign, object* objectSet, object assignedObject, cluster cl) {
    int n = get_array_length(objectSet);
    int i = 0;
    int index = -1;

    while((index < 0) & (i < n)) {
	if (objectSet[i].get_name() == assignedObject.get_name()) {
	    index = i;
	};
	i++;
    };
    if (i == n) throw NotFound();

    currentAssign[i] = cl.get_id();

    return currentAssign;
};


//Initialise les clusters pour K Means
//Pour le moment, tire aléatoirement k objets dans
//l'ensemble d'objets (algorithme R implémenté dans misc.h)
cluster* initialization(object* objectSet, int k) {
    object* initObjects = random_sampling(objectSet, k);
    cluster initClusters[k];
    int i;

    for(i=0; i < k; i++) {
	cluster cl = new cluster;
	cl.add(initObjects[i]);
	initClusters[i] = cl;
    };

    return initClusters;
};


int* get_current_assign_init(object* objectSet, cluster* clusterSet, int k, int n) {
    int currentAssign[n];
    int i;

    for(i=0; i < k; i++) {
	object* clObject = clusters[i].begin();
	currentAssign = update_assign(currentAssign, objectSet, clObject[0], clusters[i]);
    };

    return currentAssign;
};



int* init_assign(int n) {
    int i;
    int lastAssign[n];

    for(i=0; i < n; i++) {
	lastAssign[i] = -1;
    };

    return lastAssign;
};



//deepcopy
int* copy_assignment(int* currentAssign, int n) {
    int i;
    int lastAssign[n];

    for(i=0; i < n; i++) {
	//pointe vers la même case ??
	lastAssign[i] = currentAssign[i];
    };

    return lastAssign;
};



int should_stop(int* currentAssign, int* lastAssign, int n) {
    int i = 0;
    
    while(currentAssign[i] == lastAssign[i]) {
	i++;
    };
    if (i == n) {
	return 1;
    };
    return 0;
};



object* initialize_means(cluster* clusterSet, int k) {
    object means[k];
    int i;
    
    for(i=0; i < k; i++) {
	object* clObject = clusterSet[i].begin();
	means[i] = clObject[0];
    };

    return means;
};




//Cluster non vide, car fonction appelée juste après avoir ajouté un élément
object compute_mean(cluster cl) {
    float minDist = inf;
    object currentMin;
    object* obj_in_cluster = cl.begin();
    int n = get_array_length(objCluster);
    int i, j;

    for(i = 0; i < n; i++) {
	float dist = 0;
	object currentObject = objInCluster[i]
	for(j = 0; j < n; j++) {
	    dist += currentobject.d(objInCluster[j]);
	};
	if (dist < min_dist) {
	    minDist = dist;
	    currentMin = currentObject;
	};
    };
    return currentMin;
};




//dans le cas où on augmente k le nombre de clusters
//#newMean n'apparaît pas dans #means
object* update_means(int k, object* means, object obj) {
    object newMeans[k];
    int i;

    for(i=0; i < k-1; i++) {
	newMeans[i] = means[i];
    };
    newMeans[k] = obj;

    return newMeans;
};



//dans le cas où on augmente k le nombre de clusters
//#object n'apparaît pas dans un des clusters dans #clusterSet
object* update_clusters(int k, cluster* clusterSet, object obj) {
    cluster newClusterSet[k];
    int i;

    for(i=0; i < k-1; i++) {
	newClusterSet[i] = clusterSet[i];
    };
    newClusterSet[k] = new cluster;
    newClusterSet[k].add(obj);

    return newClusterSet;
};



//k est le nombre estimé initialement de clusters (borne inf)
//L'algorithme peut en créer d'autres si la distance entre
//les moyennes #m des clusters présents et l'objet #oo considéré
//est trop importante
//Typiquement: pour tout #m, dist(#m, #oo) > distLim
//L'algo retourne 0 ssi il n'y a pas eu de problème
cluster* k_means(int k, float distLim, object* objectSet) {
    cluster* clusterSet = initialization(objectSet, k);
    //#object_set doit être non vide !
    int n = get_array_length(object_set);
    int* currentAssign = get_current_assign_init(objectSet, clusterSet, k, n);
    int lastAssign = init_assign(n);
    object* means = initialize_means(clusterSet, k);
    int shouldStop = 0;
    int i, j;

    while (!shouldStop) {
	for(i=0; i < n; i++) {
	    object obj = objectSet[i];
	    float minDist = inf;
	    int clusterId = -1;
	    for(j=0; j < k; j++) {
		object mean = means[j];
		if (!(mean.get_name() == obj.get_name())) {
		    float dist = mean.d(obj);
		    if (dist < minDist & dist <= distLim) {
			minDist = dist;
			clusterId = j;
		    };
		};
	    };
	    //attribution à un autre cluster
	    if ((clusterId > 0) & !(currentAssign[i] == clusterId)) {
		clusterSet[currentAssign[i]].remove(obj);
		clusterSet[clusterId].add(obj);
		currentAssign[i] = clusterId;
	    }
	    //création d'un nouveau cluster
	    else if (clusterId < 0) {
		k++;
		means = update_means(k, means, obj);
		clusterSet = update_clusters(k, clusterSet, obj);
		clusterSet[currentAssign[i]].remove(obj);
		means[currentAssign[i]] = compute_mean(clusterSet[currentAssign]);
		currentAssign[i] = k;
	    };
	};
	shouldStop = should_stop(currentAssign, lastAssign, n);
	if (!shouldStop) {
	    lastAssign = copy_assignment(currentAssign, n);
	};
    };

    return clusterSet;
};
