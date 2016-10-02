#include "agent2cluster.h"

namespace distances{namespace ag2cl{
    template<typename DistObj>
    double D<DistObj>::d(BaseAgent* ag, BaseCluster<DistObj>* cl){
        return INFINITY;
    }
}}
