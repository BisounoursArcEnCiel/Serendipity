/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef REQUEST_REQUEST_H
#define REQUEST_REQUEST_H

#include <string>
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "../misc/misc.h"

namespace request{

class Request{    
    protected:
        typedef std::map<std::string, std::vector<int> > i_attrs_t;
        typedef std::map<std::string, std::vector<std::string> > str_attrs_t;
        i_attrs_t i_attrs;
        str_attrs_t str_attrs;
        
        int status = 0; //>0 valid
    public:

        /**
         * @param str_request - ex: att|type: val1,..,valn; att2:....
         * type : s : string, i:int if not it is s   
         */
        Request(std::string str_request){
            std::vector<std::string> attributs_data;
            boost::split(attributs_data, str_request, boost::is_any_of(";"));
            
            for(size_t i=0; i<attributs_data.size(); ++i){
                std::vector<std::string> tmp;
                boost::split(tmp, attributs_data[i], boost::is_any_of(":|"));
                
                std::string name, type, data;
                if( tmp.size() == 2 ){
                    name = tmp[0];
                    type = "s";
                    data = tmp[1];
                }else if( tmp.size() == 3 ){
                    name = tmp[0];
                    type = tmp[1];
                    data = tmp[2];
                }else{
                    status = -1;
                    fprintf(stderr, "Invalid request\n");
                    break;
                }
                    
                std::vector<std::string> values;
                boost::split(values, data, boost::is_any_of(","));
               
                boost::trim(name);
                boost::trim(type);
                for(size_t i=0; i<values.size(); ++i)
                    boost::trim(values[i]);

                if( type == "s" )
                    str_attrs[name] = values;
                else if( type == "i"){
                    std::vector<int> ivalues;
                    try{
                        for(size_t i=0; i<values.size(); i++){
                            ivalues.push_back( std::stoi(values[i],NULL) );
                        }
                    }catch( std::invalid_argument e){
                        status=-1;
                        fprintf(stderr, "Invalid integer values for attribut "  RED  "%s " RESET "\n", name.c_str());
                        break;
                    }
                    i_attrs[name] = ivalues;
                }else{
                    status = -1;
                    fprintf(stderr, "Invalid type for attribut " RED "%s " RESET "\n", name.c_str());
                    break;
                }

                    
                status = 1; 
            }
        }
        
        bool is_valid(){ return status > 1; }
        
        std::map<std::string, std::vector<int> > get_i_attrs(){ return i_attrs; }
        std::map<std::string, std::vector<std::string> > get_str_attrs(){ 
            return str_attrs;
        }

        void print(){
            for(i_attrs_t::iterator it=i_attrs.begin(); it!=i_attrs.end(); ++it){
                printf("%s=[", (it->first).c_str());
                for(size_t i=0; i<(it->second).size(); ++i)
                    printf(" %d,", (it->second)[i]); 
                printf("]\n");
            } 
            
            for(str_attrs_t::iterator it=str_attrs.begin(); it!=str_attrs.end(); ++it){
                printf("%s=[", (it->first).c_str());
                for(size_t i=0; i<(it->second).size(); ++i)
                    printf(" \"%s\",", (it->second)[i].c_str()); 
                printf("]\n");
            }
        }
};
}
#endif //REQUEST_REQUEST
