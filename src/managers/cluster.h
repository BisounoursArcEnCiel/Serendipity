/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef MANAGERS_CLUSTER_H
#define MANAGERS_CLUSTER_H

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
    class Cluster: public Manager{
        protected:
            objects_t objects;
            clusters_t clusters;

        public:
            Cluster(const char* path, objects_t& objs, 
                    clusters_t& cls) : Manager(path){
                objects = objs;
                clusters = cls;
            }

            bool init(){
                const char* cmd1 = "CREATE TABLE cluster(id bigint PRIMARY KEY \
                                    NOT NULL)";
                const char* cmd2 = "CREATE TABLE owned(cl_id bigint, \
                                    obj_id varchar(128))";
                const char* cmd[2] = {cmd1, cmd2};
                
                for(size_t i=0; i<2; ++i){
                    int rc = sqlite3_exec(db, cmd[i], callback, 0, 
                            &err_msg);
                    if(rc != SQLITE_OK){
                        fprintf(stderr, "SQL error init cluster, %d : %s\n", i, err_msg); 
                        sqlite3_free(err_msg);
                        return false;
                    }
                }
                return true;
            }
          
            bool insert(cluster_t* cl){
                std::string cmd1="INSERT INTO cluster (id) VALUES (";
                cmd1 += std::to_string(cl->get_id()) + ")";
                
                std::string cmd2="INSERT INTO owned(cl_id, obj_id)VALUES";
                cluster_t::Iterator it;
                for(it = cl->begin(); !(it == cl->end()) ; ++it){
                    if( it != cl->begin() )
                        cmd2 += "),";

                    cmd2 += "(" + std::to_string(cl->get_id())+ ",";
                    cmd2 += (*it)->get_name() + ")";
                }
                cmd2 += ")";

                std::string cmd[2] = {cmd1, cmd2};
                

                for(size_t i=0; i<2; i++){
                    int rc = sqlite3_exec(db, cmd[i].c_str(),  callback, 0, &err_msg); 
                    if( rc != SQLITE_OK ){
                        fprintf(stderr, "SQL error insert cluster, %d: %s\n cmd : \n", i, err_msg, cmd[i].c_str());
                        sqlite3_free(err_msg);
                        return false;
                    }
                }
                return true;
            }
            
            bool insert(cluster_t& cl){
                return insert(&cl);
            }

            bool insert(){
                for(clusters_t::iterator it=clusters.begin(); it!=clusters.end();
                        ++it){
                    if( !insert(it->second) )
                        return false;
                }
                return true;
            }

            static int init_cl(void* _clusters, int argc, char **argv, 
                char **col_names){
                col_names = NULL;
                assert( argc == 1);
                models::cluster_id_t id = std::stoi(argv[0]);
                clusters_t* clusters_ptr=reinterpret_cast<clusters_t*>(_clusters);        

                (*clusters_ptr)[id] = cluster_t(id); 
                return 0;
            }

            static int init_ownership(void* _pair, int argc, char **argv, 
                char **col_names){
                col_names = NULL;
                assert(argc==2);
                models::cluster_id_t cl_id = std::stoi(argv[0]);
                models::object_id_t obj_id = argv[1];
                std::pair<objects_t*, clusters_t*>* ptr=reinterpret_cast<
                    std::pair<objects_t*, clusters_t*>* >(_pair);
                
                (*(ptr->second))[cl_id].add( & ((*(ptr->first))[obj_id]) );
                return 0;
            }

            bool init_cls(){    
                const char* cmd1 = "SELECT * FROM cluster";
                const char* cmd2 = "SELECT * FROM owned";
                const char* cmd[2] = {cmd1, cmd2};
                
                std::pair<objects_t*, clusters_t*> pair0(&objects, &clusters);

                for(size_t i =0; i<2; i++){
                    int rc =0; 
                    if( i == 0)
                        rc=sqlite3_exec(db, cmd[i], init_cl, &clusters, &err_msg);
                    else
                        rc=sqlite3_exec(db, cmd[i], init_ownership, &pair0, &err_msg);
                    //int rc = sqlite3_exec(db, cmd[i], 
                    //        (i==0) ? init_cl : init_ownership, 
                    //        (i==0) ? clusters : pair0, &err_msg);
                    if( rc != SQLITE_OK ){
                        fprintf(stderr, "SQL error init clusters, %d: %s\n", i, err_msg);
                        sqlite3_free(err_msg);
                        return false;
                    }else{
                        fprintf(stdout, "Operation init clusters done successfully\n");
                    }    
                }
                return true;
            }
    };

};
#endif 

