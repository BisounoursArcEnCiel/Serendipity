/**
 * @file
 * @author
 * @date
 * @brief
 **/

#ifndef DISTANCES_OBJ2OBJ_H
#define DISTANCES_OBJ2OBJ_H

#include "../config.h"
#include "../models/cluster.h"
#include "../models/agent.h"

namespace distances{namespace obj2obj{
    using namespace models;
    
    class D{
        public:
            D(){}

            double d(BaseObject* Obj1, BaseObject* obj2);
            double operator() (BaseObject* obj1, BaseObject* obj2){
                return d(obj1, obj2);
            }
    };
}}
#endif

