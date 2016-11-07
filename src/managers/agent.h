/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef MANAGERS_AGENT_H
#define MANAGERS_AGENT_H

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
    class Agent: public Manager{
        protected:
            objects_t objects;
            clusters_t clusters;
            agents_t agents;
            
        public:
            Agent(const char* path, objects_t& objs, clusters_t& cls, 
                    agents_t& ags) : Manager(path){
                objects = objs;
                clusters = cls;
                agents = ags;
            }

            bool init(){
                const char* cmd1 = "CREATE TABLE agent(id varchar(256) PRIMARY KEY NOT NULL)";
                const char* cmd2 = "CREATE TABLE obj_pref(ag_id varchar(256), obj_id varchar(128), p float)";
                const char* cmd3 = "CREATE TABLE cl_pref(ag_id varchar(256), cl_id  bigint, p float )";
                const char* cmd[3] = {cmd1, cmd2, cmd3};
                
                for(size_t i=0; i<3; ++i){
                    int rc = sqlite3_exec(db, cmd[i], callback, 0, 
                            &err_msg);
                    if(rc != SQLITE_OK){
                        fprintf(stderr, "SQL error init agent, %zu: %s\n", i, err_msg); 
                        sqlite3_free(err_msg);
                        return false;
                    }
                }
                return true;
            }
          
            bool insert(agent_t* ag){
                std::string cmd1="INSERT INTO agent (id) VALUES (";
                cmd1 += ag->get_name() + ")";
                
                std::string cmd2="INSERT INTO obj_pref(ag_id, obj_id, p) VALUES";
                std::map<models::object_id_t, float> obj_prefs = ag->get_obj_prefs();
                for(std::map<models::object_id_t, float>::iterator it = obj_prefs.begin();
                        it != obj_prefs.end() ; ++it){
                    if( it != obj_prefs.begin() )
                        cmd2 += ",";

                    cmd2 += "(" + it->first + ",";
                    cmd2 += ag->get_name() + "," + std::to_string(it->second) +")";
                }
                cmd2 = (obj_prefs.empty()) ? "" : cmd2;

                std::string cmd3="INSERT INTO cl_pref(ag_id, cl_id, p) VALUES";
                std::map<models::cluster_id_t, float> cl_prefs = ag->get_cl_prefs();
                for(std::map<models::cluster_id_t, float>::iterator it=cl_prefs.begin();
                        it != cl_prefs.end(); ++it){
                    if( it != cl_prefs.begin())
                        cmd3 += ",";

                    cmd3 += "(" + std::to_string(it->first) + ",";
                    cmd3 += ag->get_name() + "," + std::to_string(it->second) +")";
                }
                cmd3 = (cl_prefs.empty()) ? "" : cmd3;

                std::string cmd[3] = {cmd1, cmd2, cmd3};
                

                for(size_t i=0; i<3; i++){
                    int rc = sqlite3_exec(db, cmd[i].c_str(),  callback, 0, &err_msg); 
                    if( rc != SQLITE_OK ){
                        fprintf(stderr, "SQL error insert agent, %zu: %s\ncmd : %s\n", i, err_msg, cmd[i].c_str());
                        sqlite3_free(err_msg);
                        return false;
                    }
                }
                return true;
            }
            
            bool insert(agent_t& cl){
                return insert(&cl);
            }

            bool insert(){
                for(agents_t::iterator it=agents.begin(); it!=agents.end();
                        ++it){
                    if( !insert(it->second) )
                        return false;
                }
                return true;
            }

            static int init_ag(void* _agents, int argc, char **argv, 
                char **col_names){
                assert( argc == 1 && std::string(col_names[0]) == "id");
                models::agent_id_t name = argv[0];
                agents_t* agents_ptr=reinterpret_cast<agents_t*>(_agents);        

                (*agents_ptr)[name] = agent_t(name); 
                return 0;
            }

            static int init_obj_prefs(void* _pair, int argc, char **argv, 
                char **col_names){
                assert(argc==3 && std::string(col_names[0])== "ag_id");
                models::agent_id_t ag_id = argv[0];
                models::object_id_t obj_id = argv[1];
                float p = std::stof( argv[2] );
                std::pair<objects_t*, agents_t*>* ptr=reinterpret_cast<
                    std::pair<objects_t*, agents_t*>* >(_pair);
                
                (*(ptr->second))[ag_id].set_obj( obj_id, p );
                return 0;
            }
            
            static int init_cl_prefs(void* _pair, int argc, char **argv, 
                char **col_names){
                assert(argc==3 && std::string(col_names[0]) == "ag_id");
                models::agent_id_t ag_id = argv[0];
                models::cluster_id_t cl_id = std::stoi(argv[1]);
                float p = std::stof(argv[2]); 
                std::pair<clusters_t*, agents_t*>* ptr=reinterpret_cast<
                    std::pair<clusters_t*, agents_t*>* >(_pair);
                
                (*(ptr->second))[ag_id].set_cl( cl_id,p );
                return 0;
            }

            bool init_ags(){    
                const char* cmd1 = "SELECT * FROM agent";
                const char* cmd2 = "SELECT * FROM obj_pref";
                const char* cmd3 = "SELECT * FROM cl_pref";
                const char* cmd[3] = {cmd1, cmd2, cmd3};
                
                std::pair<objects_t*, agents_t*> pair0(&objects, &agents);
                std::pair<clusters_t*, agents_t*> pair1(&clusters, &agents);

                for(size_t i =0; i<3; i++){
                    int rc =0; 
                    if( i == 0)
                        rc=sqlite3_exec(db, cmd[i], init_ag, &agents, &err_msg);
                    else if(i==2)
                        rc=sqlite3_exec(db, cmd[i], init_obj_prefs, &pair0, &err_msg);
                    else
                        rc=sqlite3_exec(db, cmd[i], init_cl_prefs, &pair1, &err_msg);
                    
                    if( rc != SQLITE_OK ){
                        fprintf(stderr, "SQL error init agents, %zu: %s\ncmd : %s\n", i, err_msg, cmd[i]);
                        sqlite3_free(err_msg);
                        return false;
                    }else{
                        fprintf(stdout, "Operation init agents done successfully\n");
                    }    
                }
                return true;
            }
    };

};
#endif 

