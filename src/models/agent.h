/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef MODELS_AGENT_H
#define MODELS_AGENT_H

#include <string>
#include <map>
#include <utility>
#include <assert.h>

#include "object.h"
#include "cluster.h"
#include "../misc/misc.h"

namespace models{
    

typedef std::string agent_id_t;

/**
 * @class BaseAgent
 * @brief
 **/
class BaseAgent{
    protected:
        /** @brief Should be a unique identifier **/
        agent_id_t name = "";
        
        std::map<object_id_t, float> obj_preferences;
        
        std::map<cluster_id_t, float> cl_preferences;

    public:
        BaseAgent(){}
        
        BaseAgent(agent_id_t _name) : name(_name){}

        agent_id_t get_name(){ return name; }
        
        std::map<object_id_t, float>& get_obj_prefs(){ return obj_preferences;}
        std::map<cluster_id_t, float>& get_cl_prefs(){ return cl_preferences;}

        void set_obj(object_id_t key, float value){
            obj_preferences.insert(std::pair<object_id_t, float>(key, value));
        }
        
        void set_cl(cluster_id_t key, float value){
            cl_preferences.insert(std::pair<cluster_id_t, float>(key, value));
        }

        
        /**
         * @warning Throw exception if key not in obj_preferences
         */
        float get(object_id_t key){
            return (obj_preferences.find(key))->second;
        }
        
        /**
         * @warning Throw exception if key not in cl_preferences
         */
        float get(cluster_id_t key){
            return (cl_preferences.find(key))->second;
        }
        
        float pref(BaseObject* obj){
            if( obj_preferences.count(obj->get_name()) == 0)
                return 0;
            else
                return obj_preferences[obj->get_name()];
        }

        float pref(BaseObject& obj){
            return pref(&obj);
        }
};

template<typename DistCl>
class Agent : public BaseAgent{
    public: 
        Agent() : BaseAgent(){}
        
        Agent(agent_id_t _name) : BaseAgent(_name){}

        template<typename DistObj>
        double dCl(Cluster<DistCl, DistObj>& cl){
            return DistCl()( this, &cl );
        }

        template<typename DistObj>
        double dCl(Cluster<DistCl, DistObj>* cl){
            return DistCl()( this, cl );
        }

        template<typename DistObj>
        float pref(Cluster<DistCl, DistObj>* cl){
            float p =0;

            typename models::Cluster<DistObj, DistObj>::Iterator it;
            for( it = cl->begin(); it!=cl->end() ; ++it)
                p += pref( (*it) );
            
            return p;
        }
};
}
#endif 
