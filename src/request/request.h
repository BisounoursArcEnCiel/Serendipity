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

namespace request{

class Request{    
    protected:
        std::map<std::string, std::vector<int> > i_attrs;
        std::map<std::string, std::vector<std::string> > str_attrs;
        
        /** @brief msg to display in case of failure */
        std::string err_msg = ""; 
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
                }else if( tmp.size() == 3 &&( tmp[1] == "s" || tmp[1] == "i")){
                    name = tmp[0];
                    type = tmp[1];
                    data = tmp[2];
                }else{
                    status = -1;
                    err_msg = "Invalid request";
                    break;
                }
                    
                std::vector<std::string> values;
                boost::split(values, data, boost::is_any_of(","));

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
                        err_msg = "Invalid argument for" +name;  
                        break;
                    }
                    i_attrs[name] = ivalues;
                }
                    
                status = 1; 
            }
        }
        
        bool is_valid(){ return status > 1; }
        
        std::map<std::string, std::vector<int> > get_i_attrs(){ return i_attrs; }
        std::map<std::string, std::vector<std::string> > get_str_attrs(){ 
            return str_attrs;
        }
};
}
#endif //REQUEST_REQUEST
