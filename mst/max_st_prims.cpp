#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = LLONG_MAX/2;

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,ll>>> g(n);

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int start;
    cin>>start;
    vector<bool> visited(n,false);
    
    priority_queue< pair<ll,ll>> pq;
    
    pq.push({0,start});

    ll mst_cost = 0;

    while(!pq.empty()){
        auto k = pq.top(); pq.pop();
        auto w = k.first;
        auto u = k.second;

        if(visited[u]) continue;
        visited[u] = true;
        mst_cost += w;

        for(auto &e: g[u]){
            auto wt = e.second;
            auto v = e.first;
            if(!visited[v]){
                pq.push({wt,v});
            }
        }
    }

    cout<<"MaxST cost = "<<mst_cost;

    return 0;
}