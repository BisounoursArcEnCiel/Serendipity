#include "obj2obj.h"

namespace distances{namespace obj2obj{
    double D::d(BaseObject* obj1, BaseObject* obj2){
        i_attrs_t i_attr1 = obj1->getIAttrs();
        str_attrs_t str_attr1 = obj1->getStrAttrs();
        
        double d_int = 0;
        for(i_attrs_t::iterator it = i_attr1.begin(); 
                it!=i_attr1.end(); ++it){
            int i2 =  obj2->getOnlyInt(it->first);    
            d_int += ((it->second).first - i2) * (it->second).second;
        }
        d_int /= i_attr1.size();

        double d_str=0;
        for(str_attrs_t::iterator it = str_attr1.begin(); 
                it!=str_attr1.end(); ++it){
            std::string s2 =  obj2->getOnlyStr(it->first);    
            std::string s1 = (it->second).first;
            d_int += (s1==s2 ? 1 : 0) * (it->second).second;
        }
        d_str /= str_attr1.size();

        return d_int + d_str;
    }
}}
