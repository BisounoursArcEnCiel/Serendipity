#include <map>
#include <string>

#include "src/distances/obj2obj.h"
#include "src/distances/cluster2cluster.h"
#include "src/distances/agent2cluster.h"


#include "src/request/request.h"
#include "src/request/handler.h"
#include "src/engine.h"

using namespace request;
using namespace std;
/**
 * @params
 *      --load path
 *      argv[argc-1] - Needed : request 
 */
int main(int argc, char** argv){
    if( argc < 2 )
        return 0;
   
       
    Engine engine;
    vector<Request> requests;

    for(int i=1; i<argc; i++){
        if( string(argv[i]) == "--load" )
            engine.load(argv[++i]);
        else{
            Request request(argv[i]); 
            request.print();
            if( !request.is_valid() )
                return -1;

            requests.push_back(request);
        }
    }
    
    for(size_t i=0; i<requests.size(); ++i){
        printf("%s", engine.process(requests[i]).c_str());
    }
    return 0;
}
