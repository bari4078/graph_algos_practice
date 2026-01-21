#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

struct DSU{
    vector<int> parent,size;

    DSU(int n){
        parent.resize(n+1);
        size.assign(n+1,1);
        for(int i=1;i<=n;i++) parent[i] = i;
    }

    int find(int x){
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b) return false;

        if(size[a] < size[b]) swap(a,b);

        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

struct Edge{
    int u,v,w;
    bool in_mst = false; // mark if edge is in MST
};

bool dfs_max(int curr, int t,int parent, vector<vector<pair<int,int>>> &mst,int &max_edge){
    if(curr == t) return true;

    for(auto e:mst[curr]){
        int next = e.first;
        int wt = e.second;
        if(next == parent) continue;
        if(dfs_max(next,t,curr,mst,max_edge)){
            max_edge = max(max_edge,wt);
            return true;
        }
    }

    return false;
}

int max_on_path(int u,int v, vector<vector<pair<int,int>>> &mst){
    int max_edge = -1;
    dfs_max(u,v,-1,mst,max_edge);
    return max_edge;
}

int main(){
    int n,m;
    cin>>n>>m;
    
    vector<Edge> edges(m);
    vector<Edge> og(m);
    for(int i=0;i<m;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        og[i] = edges[i];
    }

    sort(edges.begin(),edges.end(), [](Edge &a, Edge &b){
        return a.w < b.w; 
    });

    DSU dsu(n);

    ll mst_cost = 0;
    vector<Edge> mst_edges;

    for(auto &e:edges){
        if(dsu.unite(e.u,e.v)){
            mst_cost += e.w;
            mst_edges.push_back(e);
            e.in_mst = true; // mark edge as part of MST
        }
    }

    // Build MST adjacency list
    vector< vector< pair<int,int> > > mst(n+1);
    for(auto &e: mst_edges){
        mst[ e.u ].push_back({e.v,e.w});
        mst[ e.v ].push_back({e.u,e.w});
    }
    
    // 1️⃣ Print which edges can be in some MST
    for(auto &e:og){
        int max_w = max_on_path(e.u,e.v,mst);
        if(max_w != -1 && max_w >= e.w) cout<<"YES"<<'\n';
        else cout<<"NO"<<'\n';
    }

    // 2️⃣ Compute second MST
    ll second_mst = LLONG_MAX;
    for(auto &e:edges){
        if(!e.in_mst){ // only consider edges NOT in original MST
            int max_w = max_on_path(e.u,e.v,mst);
            if(max_w == -1) continue;
            ll new_cost = mst_cost - max_w + e.w;
            if(new_cost > mst_cost) second_mst = min(second_mst,new_cost);
        }
    }

    cout << "Second MST cost: " << second_mst << "\n";

    return 0;
}
