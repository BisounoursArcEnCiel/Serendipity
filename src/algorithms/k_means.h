#include <tuple>

#include <models/object.h>
#include <models/cluster.h>
#include <misc/random_sampling.h>
#include <config.h>

using namespace std;

typedef tuple<vector<cluster>, vector<int>, vector<object>> initResult;

//_______________________________________________________________________________
//INITIALISATION DU K-MEANS

/* Initialise les clusters pour K-Means : tire aléatoirement @k objets */
/* Renvoie les clusters, l'assignation courante des objets, la taille et les moyennes des clusters */
initResult initialization(vector<object>objectSet, int k, vector<cluster>clustersSet, vector<int>currAssign, vector<object>means) {
    initResult result;
    vector<object> reservoir;
    vector<object> initObjects = random_sampling(objectSet, reservoir, k);
    int i;

    for(i=0; i < k; ++i) {
	cluster cl;
        // Initialiser @cl
	cl.add(initObjects[i]);
        // Ajouter @cl à la liste des clusters
	clustersSet.push_back(cl);
        // Assigner l'objet @initObjects[i] à @cl
        currAssign[i] = cl.get_id();
	// Ajoute l'object comme moyenne du cluster numéro i
	means.push_back(initObjects[i]);
    };

    get<0>(result) = initClusters;
    get<1>(result) = currAssign;
    get<2>(result) = means;
    return (result);
};

//_______________________________________________________________________________
//CALCUL DE LA MOYENNE

/* Renvoie l'objet moyenne du cluster @cl */
object compute_mean(cluster cl) {
    float minDist = INFINITY;
    object currMin;
    vector<object> objVector = cl.begin();
    int size_cl = objVector.size();
    int i, j;

    // Calcul de la distance à minimiser
    for(i = 0; i < size_cl; ++i) {
	float dist = 0;
	object currObject = objVector[i];
	for(j = 0; j < size_cl; ++j) {
	    if (!(j == i)) {
		dist += currObject.d(objVector[j]);
	    };
	};
	
	if ((minDist == INFINITY) or (dist < minDist)) {
	    minDist = dist;
	    currMin = currObject;
	};
	
    };
    return (currMin);
};

//_______________________________________________________________________________
// ALGORITHME K-MEANS
// @k est une borne inférieure sur le nombre de clusters
// @T_CLUST est la distance maximale entre la moyenne d'un cluster et un objet (défini dans misc)
// @currAssign est le tableau des assignations des objets à des clusters (non initialisé)
// @clustersSet le tableau des clusters (non initialisé)
// @means le tableau des moyennes (non initialisé)
// Retourne le tableau des clusters
cluster* k_means(int k, vector<object>objectSet, vector<cluster>clustersSet, vector<int>currAssign, vector<object>means) {
    int n = objectSet.size();
    for (i = 0; i < n; ++i) currAssign.push_back(INFINITY);
    initResult res = initialization(objectSet, k, clustersSet, currAssign, means);
    clustersSet = get<0>(res);
    currAssign = get<1>(res);
    means = get<2>(res); 
    // Permet de savoir si les clusters ont bougé
    int change = 1;
    int i, j;

    while (change) {
	change = 0;
	for(i=0; i < n; ++i) {
	    object currObj = objectSet[i];
	    float minDist = T_CLUST;
	    int clusterID = INFINITY;
	    // Comparer à toutes les moyennes des clusters
	    for(j=0; j < k; ++j) {
		object currMean = means[j];
		if (currMean.get_name() == currObj.get_name()) {
		    clusterID = j;
		    break
		}
		else {
		    float dist = currMean.d(currObj);
		    if (dist < minDist) {
			minDist = dist;
			clusterID = j;
		    };
		};
	    };
	    // Cas d'attribution à un autre cluster
	    if (!(clusterID == INFINITY) & !(currAssign[i] == clusterID)) {
		change = 1;
		clustersSet[currAssign[i]].remove(obj);
		clustersSet[clusterID].add(obj);
		means[currAssign[i]] = compute_mean(clustersSet[currAssign[i]]);
		means[clusterID] = compute_mean(clustersSet[clusterID]);
		currAssign[i] = clusterID;
	    }
	    // Cas de création d'un nouveau cluster
	    else if (clusterID == INFINITY) {
		change = 1;
		++k;
		cluster cl;
		cl.add(currObj);
		clustersSet.push_back(cl);
		if (!(currAssign == INFINITY)) {
		    clustersSet[currAssign[i]].remove(obj);
		    means[currAssign[i]] = compute_mean(clustersSet[currAssign[i]]);
		};
		currAssign[i] = cl.get_id();
		means.push_back(currObj);
	    };
	};
    };

    return (clustersSet);
};
