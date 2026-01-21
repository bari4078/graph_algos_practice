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
    Edge(int a,int b,int c){
        u =a;
        v =b;
        w =c;
    }
};


int main(){
    int n,m;
    cin>>n>>m;
    
    vector<Edge> edges;

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.emplace_back(u,v,w);
    }

    sort(edges.begin(),edges.end(), [](const Edge &a, const Edge &b){
        return a.w < b.w;
    });

    int l = 0;
    int r = 0;
    int range = INT_FAST32_MAX;

    while(l < m && r< m){
        DSU dsu(n);

        for(int i=l;i<=r;i++){
            dsu.join(edges[i].u,edges[i].v);
            if(dsu.components == 1) break;
        }
        if(dsu.components == 1){
            range = min(edges[r].w - edges[l].w , range);
            l++;
            if(l>r) r = l;
        }
        else{
            r++;
        }
        
    }

    if(range < INF) cout<<range<<"\n";
    else cout<<-1;

    return 0;
}