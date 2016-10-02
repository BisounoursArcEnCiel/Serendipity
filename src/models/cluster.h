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
      
     /**
      *  @class BaseCluster
      *  @brief
      **/
    //https://accu.org/index.php/journals/389
     template<typename DistObj>
    class BaseClusterIterator : std::iterator<std::forward_iterator_tag, BaseObject >{
        protected:
            typename std::map<object_id_t, BaseObject>::iterator it;
            typedef std::map<object_id_t, BaseObject> map_t;
        public:
            typedef BaseObject value_type;
     /*       typedef size_t size_type;
            typedef ptrdiff_t  difference_type;
            typedef BaseObject         *pointer;
            typedef const BaseObject   *const_pointer;
            typedef BaseObject         &reference;
            typedef const BaseObject   &const_reference;
    */
            BaseClusterIterator(map_t& map){
                it = map.begin();
            }
    
            value_type &operator*(){ 
                return it->second; 
            }

            value_type *operator->(){ 
                return &(it->second); 
            }
            
            value_type &operator++(){
                return it++;
            }
    };

     template<typename DistObj>
     class BaseCluster{
        protected:
            static uint64_t counter;
            
            /** @brief Should be a unique identifier **/
            cluster_id_t id = 0;
            
            /** 
             * @brief
             * @warning a cluster does not owned objects
             * **/
            std::map<object_id_t, BaseObject> objects;


        public:
            BaseCluster(){
                id = counter++;
            }
            
            void add(BaseObject* obj){
                objects.insert( std::pair<object_id_t, BaseObject>(
                    obj->name, obj));     
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

            typedef BaseClusterIterator<DistObj> iterator; 
            iterator begin(){ return iterator(objects); }
            iterator end(){ return iterator(objects); }
     };
    
    template<typename Dist, typename DistObj>
    class Cluster : public BaseCluster<DistObj>{
        public:
            double d(BaseCluster<DistObj>& cl){
                return Dist()(this, &cl);
            }
            
            double d(BaseCluster<DistObj>* cl){
                return Dist()(this, cl);
            }

    };


 };
#endif 

