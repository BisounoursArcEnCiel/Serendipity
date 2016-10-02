/**
 * @file
 * @author
 * @date
 * @brief
 */

#ifndef GRAPHS_ADJACENCY_H
#define GRAPHS_ADJACENCY_H

#include <map>
#include <list>
#include <vector>

#include "../config.h"
#include "graph.h"

namespace graphs{
    /**
     * @warning Adjacency does not owned clusters
     */
    template<typename DistCl, typename DistObj>
    class Adjacency : public BaseGraph<DistCl, DistObj>{
        protected:
            using typename BaseGraph<DistCl, DistObj>::node_t;
            using typename BaseGraph<DistCl, DistObj>::node_id_t;
            using typename BaseGraph<DistCl, DistObj>::neighbours_t;

            std::map<size_t, node_t*> index;
            std::map<node_id_t, size_t> r_index;
            
            typedef std::map<size_t,double>::iterator adj_it_t;
            std::vector< std::map<size_t,double> > adjacency;
            
        public:
            Adjacency(){}

            void add(node_t* node){
                if( index.count(node.id) > 0 )
                    return;
                
                size_t n = index.size();
                r_index[node->id] = n;
                index[n] = node;

                adjacency.push_back(std::map<size_t,double>());

                for(size_t i=0; i<n; i++){
                    node_t* tmp = index[i];
                    double d = tmp->d(node);
                    if( d != INFINITY && i!=n)
                        adjacency[i][n] = d;

                    d = node->d(tmp);
                    if( d != INFINITY && i!=n)
                        adjacency[n][i] = d;
                }
            }

            void remove(node_t* node){
                if( index.count(node.id) > 0 )
                    return;

                size_t n = r_index[node->id];
                index.erase(n);
                r_index.erase(node->id);
                
                
                adjacency.erase(adjacency.begin()+n);
                for(size_t i=0; i<adjacency.size(); i++){
                    if( adjacency[i].count(n) != 0)
                        adjacency[i].erase(n);
                }
            }

            neighbours_t get_neighbours(node_id_t& id){
                size_t n = r_index[id];
                std::list<node_t*> neighbours;

                for(adj_it_t it=adjacency[n].begin(); it!=adjacency[n].end(); ++it)
                    neighbours.push_front( index[ it->first ] );
                
                return neighbours; 
            }

    };
}
#endif
