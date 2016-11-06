/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
  
#ifndef MODELS_CLUSTER_H
#define MODELS_CLUSTER_H

#include <map>
#include <utility>
#include <iterator>

#include <stddef.h>

#include "object.h"


namespace models{
         

     typedef uint64_t cluster_id_t;
     static uint64_t cluster_counter = 0;      
     /**
      *  @class BaseCluster
      *  @brief
      **/
    //https://accu.org/index.php/journals/389
     template<typename DistObj>
    class BaseIterator : std::iterator<std::forward_iterator_tag, BaseObject >{
        protected:
            typename std::map<object_id_t, BaseObject*>::iterator it;
            typedef std::map<object_id_t, BaseObject*> map_t;
        public:
            typedef BaseObject* value_type;
     /*       typedef size_t size_type;
            typedef ptrdiff_t  difference_type;
            typedef BaseObject         *pointer;
            typedef const BaseObject   *const_pointer;
            typedef BaseObject         &reference;
            typedef const BaseObject   &const_reference;
    */

            BaseIterator(){}
            
            BaseIterator(map_t& map){
                it = map.begin();
            }
            
            map_t::iterator get_it(){ return it; }

            bool operator!=(BaseIterator<DistObj> it1){
                return it != it1.get_it();
            }

           bool operator==(BaseIterator<DistObj> it1){
                return it == it1.get_it();
            }

            value_type &operator*(){ 
                return it->second; 
            }

            value_type *operator->(){ 
                return &(it->second); 
            }
            
            value_type &operator++(){
                return (it++)->second;
            }
    };

     template<typename DistObj>
     class BaseCluster{
        protected:
            /** @brief Should be a unique identifier **/
            cluster_id_t id = 0;
            
            /** 
             * @brief
             * @warning a cluster does not owned objects
             * **/
            std::map<object_id_t, BaseObject*> objects;


        public:
            BaseCluster(){
                id = cluster_counter;
            }


            BaseCluster(cluster_id_t _id):id(_id){}

            cluster_id_t get_id(){ return id;}

            void add(BaseObject* obj){
                objects[obj->get_name()]= obj;
            }
            
            void add(BaseObject& obj){
                return add( &obj);
            }

            void remove(object_id_t id){
                objects.erase(id);
            }

            void remove(BaseObject* obj){
                return remove(obj->name);
            }

            void remove(BaseObject& obj){
                return remove(obj.name);
            }
            
            bool exists(BaseObject* obj){
                return objects.count(obj->name)>0;
            }

            bool exists(BaseObject& obj){
                return exists(&obj);
            }

            /**
             * @return #(C1 \cap C2) 
             */
            int intersect(BaseCluster* cl){
                int i = 0;
                for(std::map<object_id_t, BaseObject*>::iterator it= objects.begin;
                        it != objects.end(); ++it){
                    i += cl->exists(it->second) ? 1 : 0;
                }
                return i;
            }

            /** STL Container **/
            typedef BaseObject         value_type;
            typedef BaseObject         *pointer;
            typedef const BaseObject   *const_pointer;
            typedef BaseObject         &reference;
            typedef const BaseObject   &const_reference;
            typedef size_t     size_type;
            typedef ptrdiff_t  difference_type;
            
            void clear(){
                objects.clear();
            }

            size_t size(){
                return objects.size();
            }

            bool empty(){
                return objects.empty();
            }

            size_t max_size(){
                return objects.max_size();
            }

            reference operator[] (object_id_t id){
                return objects[id];
            }

            typedef BaseIterator<DistObj> Iterator; 
            Iterator begin(){ return Iterator(objects); }
            Iterator end(){ return Iterator(objects); }


     };
    
    template<typename Dist, typename DistObj>
    class Cluster : public BaseCluster<DistObj>{
        public:
            Cluster() : BaseCluster<DistObj>(){}

            Cluster(cluster_id_t _id) : BaseCluster<DistObj>(_id){}

            double d(BaseCluster<DistObj>& cl){
                return Dist()(this, &cl);
            }
            
            double d(BaseCluster<DistObj>* cl){
                return Dist()(this, cl);
            }

    };


 };
#endif 

