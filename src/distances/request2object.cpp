#include "request2object.h"

namespace distances{namespace rq2obj{
    double D::d(Request* rq, BaseObject* obj){
        std::map<std::string, std::vector<int> > i_attrs = rq->get_i_attrs();
        std::map<std::string, std::vector<std::string> > str_attrs = rq->get_str_attrs();
        
        std::map<std::string, std::vector<int> >::iterator it_i; 
        std::map<std::string, std::vector<std::string> >::iterator it_str; 
           
        double d1 = 0;
        for(it_i= i_attrs.begin();  it_i != i_attrs.end(); ++it_i){
            float tmp = 0;
            for(size_t i =0; i< (it_i->second).size(); ++i)
                tmp += abs(obj->getOnlyInt(it_i->first) - (it_i->second)[i] );
            
            if( tmp != 0 )
                tmp /= (it_i->second).size();
            d1 += tmp;

        }
        d1 /= i_attrs.size();

        double d2 = 0;
        for(it_str= str_attrs.begin();  it_str != str_attrs.end(); ++it_str){
            float tmp = 0;
            for(size_t i =0; i< (it_str->second).size(); ++i)
                tmp += (obj->getOnlyStr(it_str->first) == (it_str->second)[i]) ? 1 : 0;
            
            if( tmp != 0 )
                tmp /= (it_str->second).size();
            d2 += tmp;

        }
        d2 /= str_attrs.size();

        return d1+d2;
    }
}}
