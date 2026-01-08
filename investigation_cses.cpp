#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <climits>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;
const ll MOD = 1e9 + 7;

vector< vector<pair<ll,ll>> > g;

ll n,m;


int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin>>n>>m;

    g.resize(n+1);
    vector<ll> dist(n+1,INF),ways(n+1,0),minF(n+1,INF),maxF(n+1,0);

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    priority_queue<
                    pair<ll,ll>,
                    vector< pair<ll,ll> >,
                    greater< pair<ll,ll> >
                >   pq;
    pq.push({0,1});
    dist[1] = 0;
    ways[1] = 1;
    minF[1] = maxF[1] = 0;
    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();

        if(dist[u] < d) continue;

        for(auto [v,w]:g[u]){
            if(dist[u] != INF && dist[v] > dist[u]+w){
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                ways[v] = ways[v]%MOD;
                minF[v] = minF[u] + 1;
                maxF[v] = maxF[u] + 1;
                pq.push({dist[v],v});
            }
            else if(dist[v] == dist[u] + w){
                ways[v] += ways[u];
                ways[v] = ways[v]%MOD;
                minF[v] = min(minF[v],minF[u]+1);
                maxF[v] = max(maxF[v],maxF[u]+1);
            }
        }
    }
    cout<<dist[n]<<' '<<ways[n]<<' '<<minF[n]<<' '<<maxF[n];
}