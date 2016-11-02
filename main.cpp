#include "src/models/agent.h"

#include "src/request/request.h"
#include "src/request/handler.h"

#include "src/distances/obj2obj.h"
#include "src/distances/agent2cluster.h"
#include "src/distances/cluster2cluster.h"

#include "src/graphs/matrix.h"
#include "src/graphs/adjacency.h"

using namespace request;

/**
 * @params
 *      argv[argc-1] - Needed : request 
 */
int main(int argc, char** argv){
    if( argc == 0)
        return 0;

    Request request(argv[argc-1]); 
    request.print();
    if( !request.is_valid() )
        return -1;
    return 0;
}
