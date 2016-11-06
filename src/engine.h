#ifndef ENGINE_H
#define ENGINE_H 

#include <unordered_map>

#include "config.h"
#include "misc/types.h"

#include "request/request.h"

#include "managers/object.h"
#include "managers/cluster.h"
#include "managers/agent.h"

#include "distances/obj2obj.h"
#include "distances/cluster2cluster.h"
#include "distances/agent2cluster.h"

using namespace std;
using namespace request;

class Engine{
    protected:
        objects_t objects;
        clusters_t clusters;
        agents_t agents;

    public:
        Engine(){}

        bool load(const char* db_path){
            bool status = true;
            
            managers::Object objectManager(db_path, objects);
            status = objectManager.init_objs();       
            objectManager.close();
            
            if(!status)
                return false;

            managers::Cluster clusterManager(db_path, objects, clusters);
            status = clusterManager.init_cls();
            clusterManager.close();

            if(!status)
                return false;


            managers::Agent agentManager(db_path, objects, clusters, agents);
            status = agentManager.init_ags();
            agentManager.close();
            
            if(!status)
                return false;

            return true;
        }

        string process(Request& request){
            Handler reqHandler;
            vector<cluster_t*> _clusters = reqHandler.prepare(clusters, request);
            return "";
        }
};

#endif
