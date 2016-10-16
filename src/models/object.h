/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef MODELS_OBJECT_H
#define MODELS_OBJECT_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <set>

#define MAX_NAME_LEN 256

namespace models{
        

    typedef std::string object_id_t;
    typedef std::string tag_t;
    typedef std::map<std::string, std::pair<int, float> > i_attrs_t;
    typedef std::map<std::string,std::pair<std::string, float> > str_attrs_t;

    /**
     * @class BaseObject
     * @brief
     **/
    class BaseObject{
        protected:
            /** @brief Should be a unique identifier **/
            object_id_t name = "";
           
            /** @brief Integer attributs **/
            i_attrs_t i_attrs;
            
            /** @brief String attributs **/
            str_attrs_t str_attrs; 
        
            /** @brief **/
            std::set<tag_t> tags;

        public:
            BaseObject(object_id_t name) : name(name){}

            BaseObject(object_id_t name, i_attrs_t i_attrs, 
            str_attrs_t str_attrs) : name(name), i_attrs(i_attrs), 
            str_attrs(str_attrs){}

            void set(std::string key, int value, float weight){
                i_attrs.insert( std::pair<std::string, std::pair<int, 
                float> >( key, std::pair<int,float>(value, weight)));
            }

            void set(std::string key, std::string value,
            float weight){
                str_attrs.insert(std::pair<std::string,std::pair<std::string, 
                float> >( key, std::pair<std::string,float>(value, weight)));
            }

            
            /**
             *
             * @warning Throw exception if key not in i_attrs
             */
            std::pair<int,float> getInt(std::string key){
                return (i_attrs.find(key))->second;
            }


            /**
             *
             * @warning Throw exception if key not in str_attrs 
             */
            std::pair<std::string,float> getStr(std::string key){
                return (str_attrs.find(key))->second;
            }
    };
    
    template<typename Dist>
    class Object : public BaseObject{
        public:
            double d(Object<Dist>& obj){
                return Dist()(this, &obj);
            }
            
            double d(Object<Dist>* obj){
                return Dist()(this, obj);
            }

	    char* get_name(Object<Dist> obj) {
		return obj.name;
	    }
    };
};
#endif 

