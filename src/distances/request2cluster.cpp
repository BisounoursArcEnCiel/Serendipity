#include "request2cluster.h"

namespace distances{namespace rq2cl{
    template<typename DistObj>
    double D<DistObj>::d(Request* rq, BaseCluster<DistObj>* cl){
        double d = 0;
        for(typename BaseCluster<DistObj>::iterator it=cl->begin(); 
                it != cl->end(); ++it){
            d += rq2obj::D().d(rq, *it); 
        }
        d /= cl->size();
        
        return d;
    }
}}
