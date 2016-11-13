#ifndef ENGINE_H
#define ENGINE_H 

#include <unordered_map>

#include "config.h"
#include "misc/types.h"

#include "request/request.h"

#include "pluggins/movielens.h"

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
        
        bool init(const char* db_path){
            bool status = true;
            
            managers::Object objectManager(db_path, objects);
            status = objectManager.init();       
            objectManager.close();
            
            if(!status)
                return false;

            managers::Cluster clusterManager(db_path, objects, clusters);
            status = clusterManager.init();
            clusterManager.close();

            if(!status)
                return false;


            managers::Agent agentManager(db_path, objects, clusters, agents);
            status = agentManager.init();
            agentManager.close();
            
            if(!status)
                return false;

            return true;

            
        }

        bool load(const char* db_path){
            bool status = true;
            printf("it's work\n");            
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

        bool import_movielens(const char* ag_path, const char* obj_path){
            if( !pluggins::movielens::import_obj(obj_path, objects))
                return false;
            return pluggins::movielens::import_ag(ag_path, agents, objects);
        }
        
        bool save(const char* db_path){
            bool status = true;

            managers::Object objectManager(db_path, objects);
            status = objectManager.insert();
            objectManager.close();

            if(!status)
                return false;

            managers::Cluster clusterManager(db_path, objects, clusters);
            status = clusterManager.insert();
            clusterManager.close();
            
            if(!status)
                return false;

            managers::Agent agentManager(db_path, objects, clusters, agents);
            status = agentManager.insert();
            agentManager.close();

            if(!status)
                return false;

            return true;
        }
        
        bool prepare(){
            assert( objects.size() > 0 && agents.size() > 0);
            return true;
        }

        string process(Request& request){
            Handler reqHandler;
            vector<cluster_t*> _clusters = reqHandler.prepare(clusters, request);
            return "";
        }

};

#endif
