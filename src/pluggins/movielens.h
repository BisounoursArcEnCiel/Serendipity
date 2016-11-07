#ifndef PLUGGINS_MOVIELENS_H
#define PLUGGINS_MOVIELENS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "../misc/types.h"
#include "../models/agent.h"
#include "../models/object.h"

using namespace std;


namespace pluggins{namespace movielens{
    bool import_ag(const char* path, agents_t& agents, objects_t& objects){
        ifstream fd(path, ios::in);

        if(fd){
            string line;
            while( getline(fd, line)){
                vector<string> values;     
                boost::split(values, line, boost::is_any_of(";"));
                
                if(values.size()!=3){
                    fprintf(stderr, "Import agents failed, incorrect %s", line.c_str());
                    return false;
                }
                
                models::agent_id_t ag_id = values[0];
                string obj_id = values[1];
                float p = stof(values[2]);
                p = (p>2) ? 1 : -1;

                if( agents.count(ag_id) > 0){
                    agents[ag_id].set_obj(obj_id, p);        
                }else{
                    agents[ag_id]=agent_t(ag_id);
                    for(objects_t::iterator it=objects.begin(); it!=objects.end(); ++it){
                        agents[ag_id].set_obj(it->first, 0);
                    }

                    agents[ag_id].set_obj(obj_id, p);
                }
            }
            
            fd.close();
            return true;
        }else
            return false;
    }

    bool import_obj(const char* path, objects_t& objects){
        ifstream fd(path, ios::in);
        vector<string> genres={
        "unknown","action", "adventure", "animation",
        "children", "comedy", "crime", "documentary", "drama", "fantasy",
        "film-noir", "horror", "musical" ,"mystery", "romance", "sci-fi",
        "thriller", "war", "western"
        };

        if(fd){
            string line;
            while( getline(fd, line)){
                vector<string> values;     
                boost::split(values, line, boost::is_any_of(";"));
                if(values.size()!=21){
                    fprintf(stderr, "Import objects failed, incorrect %s", line.c_str());
                    return false;
                }
                models::object_id_t obj_id= values[0];
                string title = values[1];
                
                objects[obj_id]=object_t(obj_id);
                objects[obj_id].set("title", title, 1);
                for(int i=2; i<21; i++){
                    objects[obj_id].set(genres[i-2], values[i], 1);
                }
            }
            
            fd.close();
            return true;
        }else
            return false;
    }


}}

#endif
