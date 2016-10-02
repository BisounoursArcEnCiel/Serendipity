/**
 * @file
 * @author
 * @date
 * @brief
 **/


#ifndef DISTANCES_CLUSTER_CLUSTER_H
#define DISTANCES_CLUSTER_CLUSTER_H

#include "../config.h"
#include "../models/cluster.h"

namespace distances{namespace cl2cl{
    using namespace models;

    template<typename DistObj>
    class D{
        public:
            D(){}
            
            double d(BaseCluster<DistObj>* cl1, BaseCluster<DistObj>* cl2);
            double operator()(BaseCluster<DistObj>* cl1, BaseCluster<DistObj>* cl2){
                return d(cl1, cl2);
            }
 
    };
}}

#endif
