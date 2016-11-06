#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <unordered_map>

#include "request.h"
#include "../misc/types.h"
#include "../models/cluster.h"
#include "../distances/request2cluster.h"

namespace request{
    using namespace models;
    using namespace distances;

    class Handler{
        protected:
             std::unordered_map<cluster_t*, double> d_tab;
        public:
            Handler(){}
            
            static bool comp(cluster_t* cl1, cluster_t* cl2, std::unordered_map<cluster_t*, double>& d_tab);
            std::vector<cluster_t*> prepare(clusters_t& cls, Request& rq);
    };

}

#endif //REQUEST_HANDLER_H
