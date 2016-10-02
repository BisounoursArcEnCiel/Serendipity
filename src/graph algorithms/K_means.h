#include <Objet.h>
#include <Cluster.h>
#include <random_sampling.h>
#include <misc.h>


int* update_assign(int* currentAssign, Objet* objectSet, Objet assignedObject, Cluster cl) {
    int n = get_array_length(objectSet);
    int i = 0;
    int index = -1;

    while((index < 0) & (i < n)) {
	if (object_set[i].equals(assignedObject)) {
	    index = i;
	};
	i++;
    };
    if (i == n) throw NotFound();

    currentAssign[i] = cl.get_identifier;

    return currentAssign;
};


//Initialise les clusters pour K Means
//Pour le moment, tire aléatoirement k objets dans
//l'ensemble d'objets (algorithme R implémenté dans misc.h)
Cluster* initialization(Objet* objectSet, int k) {
    Objet* initObjects = random_sampling(objectSet, k);
    Cluster initClusters[k];
    int i;

    for(i=0; i < k; i++) {
	Cluster cl = new Cluster;
	cl.change_identifier(i);
	cl.add_to_cluster(initObjects[i]);
	initClusters[i] = cl;
    };

    return initClusters;
};


int* get_current_assign_init(Objet* objectSet, Cluster* clusterSet, int k, int n) {
    int currentAssign[n];
    int i;

    for(i=0; i < k; i++) {
	Objet* clObject = clusters[i].enumerate_cluster();
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

Objet* initialize_means(Cluster* clusterSet, int k) {
    Objet means[k];
    int i;
    
    for(i=0; i < k; i++) {
	Objet* clObject = clusterSet[i].enumerate_cluster();
	means[i] = clObject[0];
    };

    return means;
};

//Cluster non vide, car fonction appelée juste après avoir ajouté un élément
Objet compute_mean(Cluster cl) {
    float minDist = inf;
    Objet currentMin;
    Objet* obj_in_cluster = cl.enumerate_cluster();
    int n = get_array_length(objCluster);
    int i, j;

    for(i = 0; i < n; i++) {
	float dist = 0;
	Objet currentObject = objInCluster[i]
	for(j = 0; j < n; j++) {
	    dist += currentObject.distance_to_object(objInCluster[j]);
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
Objet* update_means(int k, Objet* means, Objet object) {
    Objet newMeans[k];
    int i;

    for(i=0; i < k-1; i++) {
	newMeans[i] = means[i];
    };
    newMeans[k] = object;

    return newMeans;
};



//dans le cas où on augmente k le nombre de clusters
//#object n'apparaît pas dans un des clusters dans #clusterSet
Objet* update_clusters(int k, Cluster* clusterSet, Objet object) {
    Cluster newClusterSet[k];
    int i;

    for(i=0; i < k-1; i++) {
	newClusterSet[i] = clusterSet[i];
    };
    newClusterSet[k] = new Cluster;
    newClusterSet[k].add_to_cluster(object);

    return newClusterSet;
};



//k est le nombre estimé initialement de clusters (borne inf)
//L'algorithme peut en créer d'autres si la distance entre
//les moyennes #m des clusters présents et l'objet #oo considéré
//est trop importante
//Typiquement: pour tout #m, dist(#m, #oo) > distLim
//L'algo retourne 0 ssi il n'y a pas eu de problème
Cluster* k_means(int k, float distLim, Objet* objectSet) {
    Cluster* clusterSet = initialization(objectSet, k);
    //#object_set doit être non vide !
    int n = get_array_length(object_set);
    int* currentAssign = get_current_assign_init(objectSet, clusterSet, k, n);
    int lastAssign = init_assign(n);
    Objet* means = initialize_means(clusterSet, k);
    int shouldStop = 0;
    int i, j;

    while (!shouldStop) {
	for(i=0; i < n; i++) {
	    Objet object = objectSet[i];
	    float minDist = inf;
	    int clusterId = -1;
	    for(j=0; j < k; j++) {
		Objet mean = means[j];
		if (!(mean.equals(object))) {
		    float dist = mean.distance_to_object(object);
		    if (dist < minDist & dist <= distLim) {
			minDist = dist;
			clusterId = j;
		    };
		};
	    };
	    //attribution à un autre cluster
	    if ((clusterId > 0) & !(currentAssign[i] == clusterId)) {
		clusterSet[currentAssign[i]].remove_from_cluster(object);
		clusterSet[clusterId].add_to_cluster(object);
		currentAssign[i] = clusterId;
	    }
	    //création d'un nouveau cluster
	    else if (clusterId < 0) {
		k++;
		means = update_means(k, means, object);
		clusterSet = update_clusters(k, clusterSet, object);
		clusterSet[currentAssign[i]].remove_from_cluster(object);
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
