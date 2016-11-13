//http://cgit.marty.website/olivier/notebook.git/

// Implementation of Dijkstra's algorithm using adjacency lists
// and priority queue for efficiency.
// Running time: O(|E| log |V|)
// USAGE: edges: pair of weight/destination, source, target

#include <utility>
#include <queue>
#include "../misc/misc.h"

using namespace std;

typedef pair<uint64_t, uint64_t> PII;
typedef vector<pair<uint64_t, uint64_t>> VPII;
typedef vector<uint64_t> VI;
VI Dijkstra(VPII edges, uint64_t s) {
  // use priority queue in which top element has the "smallest" priority
  priority_queue<PII, VPII, greater<PII>> Q;
  VI dist(edges.size(), INFINITY), dad(edges.size(), -1);
  Q.push(pair<uint64_t, uint64_t>(0, s));
  dist[s] = 0;
  while(!Q.empty()){
    PII p = Q.top();
    Q.pop();
    uint64_t here = p.second;
/*    for(VPII::iterator it=edges[here].begin(); it!=edges[here].end(); it++){
      if(dist[here] + it->first < dist[it->second]){
        dist[it->second] = dist[here] + it->first;
        dad[it->second] = here;
        Q.push (pair<uint64_t, uint64_t>(dist[it->second], it->second));
      }
    }*/
  }
  // dist contains distances
  return (dist);
}
