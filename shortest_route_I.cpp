#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const long long INF = 1e20;

int main(){
    long long n,m;
    cin>>n>>m;

    vector< vector< pair<long long,long long> > > g(n+1);
    vector<long long> dist(n+1,INF);
    priority_queue<
                    pair<long long,long long>,
                    vector< pair<long long,long long> >,   
                    greater< pair<long long,long long> >
                > pq;

    for(long long i=0;i<m;i++){
        long long u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    dist[1] = 0;
    pq.push({0,1});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();

        if(dist[u] != d) continue;

        for(auto &edge:g[u]){
            long long v = edge.first;
            long long w = edge.second;

            if(d+w<dist[v]){
                dist[v] = d + w;
                pq.push({dist[v],v});
            }
        }
    }

    for(long long i=1;i<n+1;i++){
        cout<<dist[i]<<' ';
    }
}