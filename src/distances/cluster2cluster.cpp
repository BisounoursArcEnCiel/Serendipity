#include "cluster2cluster.h"

namespace distances{namespace cl2cl{
    template<typename DistObj>
    double D<DistObj>::d(BaseCluster<DistObj>* cl1, BaseCluster<DistObj>* cl2){
        typename BaseCluster<DistObj>::Iterator it1 = cl1.begin();
        double d1 =  static_cast<double>(cl1->intersect(cl2));
        d1 /= static_cast<double>(cl1->size()+cl2->size);

        double d2 = 0;
        printf("faut il rajouter la distance où on parcours tous les agents\n");
        assert(false);
        return d1 + d2;
    }
}}
