#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <climits>
using namespace std;

long long n,m;
const long long INF = LLONG_MAX;

int main(){
    cin>>n>>m;

    vector< vector< pair<long long,long long> > > g(n+1);

    for(long long i=0;i<m;i++){
        long long u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    vector< vector<long long> > dist(n+1, vector<long long> (2,INF));


    dist[1][0] = 0;

    priority_queue< 
                    pair< long long, pair<long,long> >,
                    vector< pair< long long, pair<long,long> > >,
                    greater<pair< long long, pair<long,long> > > 
                >   pq;

    pq.push({0,{1,0}});

    while(!pq.empty()){
        auto d = pq.top().first;
        auto u = pq.top().second.first;
        auto usedDiscount = pq.top().second.second;
        pq.pop();
        if(d > dist[u][usedDiscount]) continue;
        if(usedDiscount == 1){
            for(auto &edge: g[u]){
                long long v = edge.first;
                long long w = edge.second;

                if(dist[u][1] + w < dist[v][1]){
                    dist[v][1] = dist[u][1] + w;
                    pq.push({dist[v][1],{v,1}});
                }
            }
        }
        else if(usedDiscount == 0){
            for(auto &edge: g[u]){
                long long v = edge.first;
                long long w = edge.second;

                if(dist[u][0] + w/2 < dist[v][1]){
                    dist[v][1] = dist[u][0] + w/2;
                    pq.push({dist[v][1],{v,1}});
                }
                if(dist[u][0] + w < dist[v][0]){
                    dist[v][0] = dist[u][0] + w;
                    pq.push({dist[v][0],{v,0}});
                }
            }
        }
    }

    cout<<dist[n][1];
    return 0;
}   