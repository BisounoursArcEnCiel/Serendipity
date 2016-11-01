#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <unordered_map>

#include "request.h"
#include "../models/cluster.h"
#include "../distances/request2cluster.h"

namespace request{
    using namespace models;
    using namespace distances;

    template<typename DObject>
    class Handler{
        protected:
             std::unordered_map<BaseCluster<DObject>*, double> d_tab;
        public:
            Handler(){}
            
            bool comp(BaseCluster<DObject>* cl1, BaseCluster<DObject>* cl2);
            void prepare(std::vector<BaseCluster<DObject>*>& cls, Request* rq);
    };

}

#endif //REQUEST_HANDLER_H
