/**
 * @file
 * @author
 * @date
 * @brief
 **/

#ifndef DISTANCES_AGENT2CLUSTER_H
#define DISTANCES_AGENT2CLUSTER_H

#include "../config.h"
#include "../models/cluster.h"
#include "../models/agent.h"

namespace distances{namespace ag2cl{
    using namespace models;
    
    template<typename DistObj>
    class D{
        public:
            D(){}

            double d(BaseAgent* ag, BaseCluster<DistObj>* cl);
            double operator() (BaseAgent* ag, BaseCluster<DistObj>* cl){
                return d(ag, cl);
            }
    };
}}
#endif

