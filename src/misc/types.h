#ifndef MISC_TYPES_H
#define MISC_TYPES_H

#include <unordered_map>

#include "../models/object.h"
#include "../models/cluster.h"
#include "../models/agent.h"

#include "../distances/obj2obj.h"
#include "../distances/cluster2cluster.h"
#include "../distances/agent2cluster.h"

using namespace distances;

typedef obj2obj::D d_obj; 
typedef cl2cl::D<d_obj> d_cl;

typedef models::Object<obj2obj::D> object_t;
typedef models::Cluster<cl2cl::D<obj2obj::D>, obj2obj::D> cluster_t;
typedef models::Agent<ag2cl::D<cl2cl::D<obj2obj::D> > > agent_t;

typedef std::unordered_map<models::object_id_t, object_t> objects_t;
typedef std::unordered_map<models::cluster_id_t, cluster_t> clusters_t;
typedef std::unordered_map<models::agent_id_t, agent_t> agents_t;

#endif
