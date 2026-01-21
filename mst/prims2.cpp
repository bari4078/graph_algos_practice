#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main(){
    int n,m;
    cin>>n>>m;
    vector< vector<pair<int,ll> > > g(n+1);

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    priority_queue<
                    pair<int,ll>,
                    vector< pair<int,ll> >,
                    greater< pair<int,ll> >
                > pq;

    vector<bool> visited(n+1);
    ll mst_cost = 0;
    int node_count = 0;

    pq.push({0,1});

    while(!pq.empty()){
        auto k = pq.top();
        auto w = k.first;
        auto u = k.second;

        pq.pop();
        if(visited[u]) continue;
        visited[u] = true;
        mst_cost += w;
        node_count++;

        for(auto &e:g[u]){
            auto v = e.first;
            auto wt = e.second;

            if(!visited[v]){
                pq.push({wt,v});
            }
        }
    }

    if(node_count != n) cout<<"IMPOSSIBLE";
    else cout<<mst_cost;

    return 0;
}