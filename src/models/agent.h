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

#include "object.h"
#include "cluster.h"

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
        BaseAgent();

        void set(object_id_t key, float value){
            obj_preferences.insert(std::pair<object_id_t, float>(key, value));
        }
        
        void set(cluster_id_t key, float value){
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
            printf("must be defined\n");
            assert(false);
            return INFINITY;
        }

        float pref(BaseObject& obj){
            return pref(&obj);
        }
};

template<typename DistCl>
class Agent : public BaseAgent{
    public: 
        template<typename DistObj>
        double dCl(Cluster<DistCl, DistObj>& cl){
            return DistCl()( this, &cl );
        }

        template<typename DistObj>
        double dCl(Cluster<DistCl, DistObj>* cl){
            return DistCl()( this, cl );
        }
};
}
#endif 
