#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = LLONG_MAX/2;


void mst_component(vector< vector<pair<int,ll> >> &g,
                    vector<bool> &visited, vector< pair<int,int> > &mst_edges,
                    ll &mst_cost, int start){
    priority_queue< pair<ll,pair<int,int>>,
                    vector< pair <ll, pair<int,int> > >,
                    greater< pair< ll,pair<int,int> > >
                > pq;
    pq.push({0,{start,-1}});
    
    while(!pq.empty()){
        auto key = pq.top().first;
        auto u = pq.top().second.first;
        auto par_u = pq.top().second.second;

        pq.pop();

        if(visited[u]) continue;
        visited[u] = true;
        mst_cost += key;

        if(par_u != -1) mst_edges.push_back({par_u,u});

        for(auto &e: g[u]){
            auto wt = e.second;
            auto v = e.first;
            if(!visited[v]){
                pq.push({wt,{v,u}});
            }
        }
    }
}


int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,ll>>> g(n);
    vector<bool> visited(n,false);
    vector<pair<int,int>> mst_edges;
    
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    int start;
    cin>>start;

    ll mst_cost = 0;

    mst_component(g,visited,mst_edges,mst_cost,start);

    for(int i=0;i<n;i++){
        if(!visited[i]){
            mst_component(g,visited,mst_edges,mst_cost,i);
        }
    }
    
    
    cout<<"Total weight "<<mst_cost<<"\n";

    for(auto &e:mst_edges){
        cout<<e.first<<" "<<e.second<<"\n";
    }

    return 0;
}