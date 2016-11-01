#include "handler.h"

namespace request{
    template<typename DObject>
    bool Handler<DObject>::comp(BaseCluster<DObject>* cl1, BaseCluster<DObject>* cl2){
        return d_tab[cl1] < d_tab[cl2];
    }

    template<typename DObject>
    void Handler<DObject>::prepare(std::vector<BaseCluster<DObject>*>&cls, Request* rq){
        for(size_t i=0; i<cls.size(); ++i)
            d_tab[cls[i]] = rq2cl::D<DObject>().d(rq, cls[i]); 
        
        std::sort(cls.begin(), cls.end(), comp);
    }

}
