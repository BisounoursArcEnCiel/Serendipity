/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef MANAGERS_OBJECT_H
#define MANAGERS_OBJECT_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <set>

#include <boost/algorithm/string.hpp>
#include <sqlite3.h>

#include "utility.h"
#include "manager.h"
#include "../models/object.h"
#include "../misc/types.h"

namespace managers{
    class Object: public Manager{
        protected:
            objects_t objects;
        public:
            Object(const char* path, objects_t& objs) : Manager(path){
                objects = objs;
            }

            bool init(){
              const char* cmd = "CREATE TABLE object(id varchar(128), i_attrs text, str_attrs text)";
                
              int rc = sqlite3_exec(db, cmd, callback, 0, &err_msg);
              if(rc != SQLITE_OK){
                    fprintf(stderr, "SQL error : %s\n", err_msg); 
                    sqlite3_free(err_msg);
                    return false;
              }
              return true;
            }
            
            std::string protect(std::string s){ return s; }//todo

            std::string value(models::BaseObject* obj){
                std::string cmd="";
                models::i_attrs_t i_attrs = obj->get_i_attrs();
                models::str_attrs_t str_attrs = obj->get_str_attrs();

                cmd += obj->get_name()+",";
                
                for(models::i_attrs_t::iterator it = i_attrs.begin(); 
                        it!=i_attrs.end(); ++it){
                    cmd += protect(it->first) + ":"; 
                    cmd += std::to_string((it->second).first) + "|";
                    cmd += std::to_string((it->second).second) + ";";
                }
                
                for(models::str_attrs_t::iterator it = str_attrs.begin();
                        it!=str_attrs.end(); ++it){
                    cmd += protect(it->first) + ":";
                    cmd += protect((it->second).first) + "|";
                    cmd += std::to_string((it->second).second) + ";";
                }

                return cmd;
            }

            bool insert(models::BaseObject* obj){
                std::string cmd="INSERT INTO object (id, i_attrs, str_attrs) ";
                cmd += "VALUES(" + value(obj) +")";
                
                int rc = sqlite3_exec(db, cmd.c_str(),  callback, 0, 
                        &err_msg);
                if( rc != SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    return false;
                }else{
                    fprintf(stdout, "Records created successfully\n");
                }
                return true;
            }
            bool insert(models::BaseObject& obj){
                return insert(&obj);
            }

            bool insert(){
                for(objects_t::iterator it=objects.begin(); it!=objects.end(); 
                        ++it){
                    if( !insert(it->second))
                        return false;
                }
                return true;
            }


            static int init_obj(void* _objects, int argc, char **argv,
                    char**col_names){
                assert(argc == 3);
                const std::string name = argv[0]; 
                const std::string i_attrs = argv[1];
                const std::string str_attrs = argv[2];
                objects_t* objects_ptr = reinterpret_cast<objects_t*>(_objects);
                (*objects_ptr)[name] = object_t(name);
                
                    
                std::vector<std::string> values_i;
                std::vector<std::string> values_str;
                boost::split(values_i, i_attrs, boost::is_any_of(";"));
                boost::split(values_str, str_attrs, boost::is_any_of(";"));

                for(size_t i=0; i<values_i.size(); ++i){
                    std::vector<std::string> tmp;
                    boost::split(tmp, values_i[i], boost::is_any_of(":|"));

                    if( tmp.size() == 3){
                        fprintf(stderr, "Bdd corrupted\n");
                        exit(-1);
                    }

                    (*objects_ptr)[name].set(tmp[1], std::stoi(tmp[1]), std::stof(tmp[2]));
                }
                
                for(size_t i=0; i<values_str.size(); ++i){
                    std::vector<std::string> tmp;
                    boost::split(tmp, values_str[i], boost::is_any_of(":|"));

                    if( tmp.size() == 3){
                        fprintf(stderr, "Bdd corrupted\n");
                        exit(-1);
                    }

                    (*objects_ptr)[name].set(tmp[1], tmp[1], std::stof(tmp[2]));
                }
                return 0;
            }
            
            bool init_objs(){
                const char* cmd = "SELECT * FROM object";
                
                int rc = sqlite3_exec(db, cmd, init_obj, &objects, &err_msg);
                if( rc !=SQLITE_OK ){
                    fprintf(stderr, "SQL error: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    return false;
                }else{
                    fprintf(stdout, "Operation done successfully\n");
                }
                return true;
            }
    };

};
#endif 

