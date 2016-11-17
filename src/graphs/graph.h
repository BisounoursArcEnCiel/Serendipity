/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
  
#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>

#include "../models/cluster.h"
namespace graphs{
    using namespace models;
     /**
      *  @class BaseGraph
      *  @brief
      *  @warning a graph does not owned clusters
      **/
    template<typename DistCl, typename DistObj>
    class BaseGraph{
        protected:  
            typedef std::list<Cluster<DistCl, DistObj>*> neighbours_t;
            typedef Cluster<DistCl, DistObj> node_t;
            typedef cluster_id_t node_id_t;

            static uint64_t counter;
            uint64_t id = 0;
       
            
            std::map<size_t, node_t*> index;
            std::map<node_id_t, size_t> r_index;

        public:
            BaseGraph(){
                id = counter++;
            }

            virtual void add(node_t* cl) = 0;
            void add(node_t& cl){
                return add(*cl);
            }

            /**
             * @warning Throw exception if cluster not in graph
             */
            virtual void remove(node_id_t id) = 0;
            void remove(node_t* cl){
                return remove(cl->id);
            }
            void remove(node_t& cl){
                return remove(cl.id);
            }

            
            /**
             * @brief Get neighbours of current node
             */
            virtual neighbours_t get_neighbours(node_id_t id) = 0;
            neighbours_t operator [](node_id_t id){
                return get_neighbours(id);
            }
            neighbours_t operator [](node_t* cl){
                return get_neighbours(cl->id);
            }
            neighbours_t operator [](node_t& cl){
                return get_neighbours(cl.id);
            }
            

            /**
             * @brief Get neighbours of current node
             */
            virtual double get(node_id_t id1, node_id_t id2) = 0;
            double operator ()(node_id_t id1, node_id_t id2){
                return get(id1, id2);
            }
            double operator ()(node_t* cl1, node_t* cl2){
                return get(cl1->id, cl2->id);
            }
            double operator ()(node_t& cl1, node_t& cl2){
                return get(cl1.id, cl2.id);
            }
     };

 };
#endif 

