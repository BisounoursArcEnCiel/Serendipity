#include "agent2cluster.h"

namespace distances{namespace ag2cl{
    template<typename DistObj>
    double D<DistObj>::d(BaseAgent* ag, BaseCluster<DistObj>* cl){
        double d = 0;
        for(typename BaseCluster<DistObj>::iterator it=cl->begin(); 
                it != cl->end(); ++it){
            d += ag->pref(*it); 
        }
        d /= cl->size();
        
        return d;
    }
}}
