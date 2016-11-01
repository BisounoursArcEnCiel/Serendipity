/**
 * @file
 * @author
 * @date
 * @brief
 **/

#ifndef DISTANCES_REQUEST2CLUSTER_H
#define DISTANCES_REQUEST2CLUSTER_H

#include "../config.h"
#include "../models/cluster.h"
#include "../request/request.h"
#include "request2object.h"

namespace distances{namespace rq2cl{
    using namespace models;
    using namespace request;

    template<typename DistObj>
    class D{
        public:
            D(){}

            double d(Request* rq, BaseCluster<DistObj>* cl);
            double operator() (Request* rq, BaseCluster<DistObj>* cl){
                return d(rq, cl);
            }
    };
}}
#endif

