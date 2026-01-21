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
        u=a; v=b; w=c;
    }
};

int main(){
    int n;
    cin>>n;

    vector< pair<int,int> > x;
    vector< pair<int,int> > y;
    vector< pair<int,int> > z;

    for(int i=0;i<n;i++){
        int cx,cy,cz;
        cin>>cx>>cy>>cz;
        x.push_back({i,cx});
        y.push_back({i,cy});
        z.push_back({i,cz});
    }

    sort(x.begin(),x.end(), [](const pair<int,int> &a,const pair<int,int> &b){
        return a.second < b.second;
    });

    sort(y.begin(),y.end(), [](const pair<int,int> &a,const pair<int,int> &b){
        return a.second < b.second;
    });

    sort(z.begin(),z.end(), [](const pair<int,int> &a,const pair<int,int> &b){
        return a.second < b.second;
    });
    
    vector<Edge> edges;

    for(int i=1;i<n;i++){
        int u = x[i-1].first;
        int v = x[i].first;
        int w = abs(x[i].second - x[i-1].second);
        edges.emplace_back(u,v,w);

        int uy = y[i-1].first;
        int vy = y[i].first;
        int wy = abs(y[i].second - y[i-1].second);
        edges.emplace_back(uy,vy,wy);

        int uz = z[i-1].first;
        int vz = z[i].first;
        int wz = abs(z[i-1].second-z[i].second);
        edges.emplace_back(uz,vz,wz);
    }

    sort(edges.begin(),edges.end(),[](const Edge &a,const Edge &b){
        return a.w < b.w;
    });

    DSU dsu(n);
    int mst_cost = 0;
    int count = 0;
    for(auto &e: edges){
        if(dsu.join(e.u,e.v)){
            mst_cost += e.w;
            count++;
            if(count == n-1) break;
        }
    }

    cout<<mst_cost;

    return 0;
}