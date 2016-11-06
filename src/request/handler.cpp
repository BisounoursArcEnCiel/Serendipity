#include "handler.h"

namespace request{
    bool Handler::comp(cluster_t* cl1, cluster_t* cl2,
            std::unordered_map<cluster_t*, double>& d_tab){
        return d_tab[cl1] < d_tab[cl2];
    }

    std::vector<cluster_t*> Handler::prepare(clusters_t &cls, Request& rq){
        std::vector<cluster_t*> _cls;
        cls.reserve(cls.size());
        for(size_t i=0; i<cls.size(); ++i){
            d_tab[&cls[i]] = rq2cl::D<d_obj>().d(&rq, dynamic_cast<BaseCluster<d_obj>* >(&(cls[i]))); 
            _cls[i] = &(cls[i]);
        }    
        
        using namespace std::placeholders;
        std::sort(_cls.begin(), _cls.end(), std::bind(comp, _1, _2, d_tab) );
        return _cls;
    }

}
