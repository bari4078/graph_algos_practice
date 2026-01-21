#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

struct DSU{
    vector<int> parent,size;
    int components;
    DSU(int n){
        parent.resize(n+1);
        size.assign(n+1,1);
        for(int i=0;i<=n;i++) parent[i] = i;
        components = n;
    }

    int find(int a){
        if(parent[a] == a) return parent[a];
        return parent[a] = find(parent[a]);
    }

    bool join(int a,int b){
        a = find(a);
        b = find(b);

        if(a == b) return false;
        if(size[b] > size[a]) swap(a,b);
        parent[b] = a;
        size[a] += size[b];
        components--;
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
        int u,v,w;
        cin>>u>>v>>w;
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    sort(edges.begin(),edges.end(),[](Edge &a, Edge &b){
        return a.w < b.w;
    });

    DSU dsu(n);
    ll mst_cost = 0;
    int count = 0;
    for(auto &e: edges){
        if(dsu.join(e.u,e.v)){
            mst_cost += e.w;
            count++;
        }
    }

    if(dsu.components == 1){
        cout<<mst_cost;
        return 0;
    }

    cout<<"IMPOSSIBLE";
    return 0;
}