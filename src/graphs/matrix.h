/**
 * @file
 * @author
 * @date
 * @brief
 */

#ifndef GRAPHS_MATRIX_H
#define GRAPHS_MATRIX_H

#include <vector>
#include <list>

#include "../config.h"
#include "graph.h"

namespace graphs{
    /**
     * @warning Matrix does not owned clusters
     */
    template<typename DistCl, typename DistObj>
    class Matrix : public BaseGraph<DistCl, DistObj>{
        protected:
            using typename BaseGraph<DistCl, DistObj>::node_t;
            using typename BaseGraph<DistCl, DistObj>::node_id_t;
            using typename BaseGraph<DistCl, DistObj>::neighbours_t;

            std::map<size_t, node_t*> index;
            std::map<node_id_t, size_t> r_index;

            std::vector< std::vector<double> > matrix;
            
        public:
            Matrix(){}

            void add(node_t* node){
                if( index.count(node.id) > 0 )
                    return;
                
                size_t n = index.size();
                r_index( std::pair<node_id_t, size_t>(node->id, n));
                index.insert( std::pair<size_t, node_t*>(n, node));
                matrix.push_back( std::vector<double>(n+1, INFINITY));
                matrix[n][n] = 0;

                for(size_t i=0; i<n; i++){
                    double d = node->d(index(i));
                    d = (d > D_LIM) ? INFINITY : d;

                    matrix[i].push_back(d);
                    matrix[n][i] = d;               
                }
            }

            void remove(node_t* node){
                if( index.count(node.id) > 0 )
                    return;

                size_t n = r_index[node->id];
                index.erase(n);
                r_index.erase(node->id);
                matrix.erase(matrix.begin()+n);
                for(size_t i=0; i<matrix.size(); i++)
                    matrix[i].erase(matrix[i].begin()+n);
            }

            neighbours_t get_neighbours(node_id_t& id){
                size_t n = r_index[id];
                neighbours_t neighbours;
                
                for(size_t i=0; i<matrix.size(); i++)
                    if( matrix[n][i] != INFINITY && n != i )
                        neighbours.push_front( index[i]);

                return neighbours;
            }

            double get(node_id_t& id1, node_id_t& id2){
                size_t n1 = r_index[id1];
                size_t n2 = r_index[id2];

                return matrix[n1][n2];
            }
    };
}
#endif
