#include <bits/stdc++.h>
#include <tuple>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n+1);
        sz.assign(n+1,1);
        for(int i=0;i<=n;i++) parent[i]=i;
    }
    int find(int x) { return x==parent[x]?x:parent[x]=find(parent[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        parent[b]=a; sz[a]+=sz[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        int n,m;
        long long k;
        cin >> n >> m >> k;
        vector<tuple<long long,int,int>> edges;
        for(int i=0;i<m;i++){
            int u,v;
            long long s;
            cin >> u >> v >> s;
            edges.push_back({s,u,v});
        }

        sort(edges.begin(), edges.end()); // ascending order

        DSU dsu(n);
        long long max_edge_in_tree = 0;
        int count = 0;
        for(auto &[s,u,v] : edges){
            if(dsu.unite(u,v)){
                max_edge_in_tree = max(max_edge_in_tree,s);
                count++;
                if(count==n-1) break;
            }
        }

        long long answer = abs(max_edge_in_tree - k);
        cout << answer << "\n";
    }
}
