/**
 * @file 
 * @author 
 * @date 
 * @brief 
 **/
 
#ifndef MANAGERS_MANAGER_H
#define MANAGERS_MANAGER_H

#include <sqlite3.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace managers{
    class Manager{
        protected:
            sqlite3* db=NULL;
            char *err_msg = NULL;
        public:
            Manager(const char* path){
                if( sqlite3_open(path, &db) ){
                    fprintf(stderr, "Can not open database at %s : %s", path, 
                            sqlite3_errmsg(db));
                    exit(-1);
                }
            }

            ~Manager(){
                if( db!=NULL )
                    sqlite3_close(db);
                db = NULL;
            }
            
            void close(){
                if( db!=NULL)
                    sqlite3_close(db);
                db = NULL;
            }

            static int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName){
                assert(NotUsed == NULL);
                int i;
                for(i=0; i<argc; i++){
                    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
                }
                printf("\n");
                return 0;
            }

            virtual bool init(){ return true;}
    };

};
#endif 

