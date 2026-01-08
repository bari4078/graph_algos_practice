#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

using ll = long long;
const ll inf = 1e8;

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,ll>>> g(n);

    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin>>u>>v>>w;

        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    int start = 0,end = n-1;
    vector<ll> d1(n,inf),d2(n,inf);

    priority_queue<
        pair<ll,int>, 
        vector<pair<ll,int>>, 
        greater<pair<ll,int>>> pq;

    d1[start] = 0;
    pq.push({start,0});

    while(!pq.empty()){
        auto [dist,u] = pq.top(); pq.pop();

        if(dist > d2[u]) continue;

        for(auto [v,w] : g[u]){
            ll nd = dist + w;

            if(nd < d1[v]){
                d2[v] = d1[v];
                d1[v] = nd;
                pq.push({d1[v],v});
            }

            else if(nd > d1[v] && nd < d2[v]){
                 d2[v] = nd;
                 pq.push({d2[v],v});
            }
        }
    }
}