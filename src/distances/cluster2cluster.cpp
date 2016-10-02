#include "cluster2cluster.h"

namespace distances{namespace cl2cl{
    template<typename DistObj>
    double D<DistObj>::d(BaseCluster<DistObj>* cl1, BaseCluster<DistObj>* cl2){
       return INFINITY;
    }
}}
