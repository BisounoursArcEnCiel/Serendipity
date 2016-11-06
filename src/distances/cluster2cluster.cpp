#include "cluster2cluster.h"

namespace distances{namespace cl2cl{
    template<typename DistObj>
    double D<DistObj>::d(BaseCluster<DistObj>* cl1, BaseCluster<DistObj>* cl2){
    double d1 = static_cast<double>(cl1->size()+cl2->size);
    d1 -=  2*static_cast<double>(cl1->intersect(cl2));
    return d1;
    }
}}
