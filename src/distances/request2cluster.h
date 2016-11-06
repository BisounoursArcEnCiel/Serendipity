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

            double d(Request* rq, BaseCluster<DistObj>* cl){
                double d = 0;
                for(typename BaseCluster<DistObj>::Iterator it=cl->begin(); 
                        it != cl->end(); ++it){
                    d += rq2obj::D().d(rq, *it); 
                }
                d /= cl->size();
                
                return d;

            }
            double operator() (Request* rq, BaseCluster<DistObj>* cl){
                return d(rq, cl);
            }
    };
}}
#endif

