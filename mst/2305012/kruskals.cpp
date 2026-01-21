#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

struct DSU{
    vector<int> parent,size;

    DSU(int n){
        parent.resize(n);
        size.assign(n,1);
        for(int i=0;i<n;i++){
            parent[i] = i;
        }
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
};

int main(){
    int n,m;
    cin>>n>>m;
    
    vector<Edge> edges(m);

    for(int i=0;i<m;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }
    int start;
    cin>>start;
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
        }
    }

    cout<<"Total weight "<<mst_cost<<"\n";

    for(auto &e:mst_edges){
        cout<<e.u<<" "<<e.v<<"\n";
    }
}