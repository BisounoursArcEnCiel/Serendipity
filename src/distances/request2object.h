/**
 * @file
 * @author
 * @date
 * @brief
 **/

#ifndef DISTANCES_REQUEST2OBJECT_H
#define DISTANCES_REQUEST2OBJECT_H

#include <cstdlib>
#include <map>

#include "../config.h"
#include "../models/object.h"
#include "../request/request.h"

namespace distances{namespace rq2obj{
    using namespace models;
    using namespace request;
    
    class D{
        public:
            D(){}

            double d(Request* rq, BaseObject* obj);
            double operator() (Request* rq, BaseObject* obj){
                return d(rq, obj);
            }
    };
}}
#endif

