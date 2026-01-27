#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = INT_MAX/2;

struct Edge {
    int v;
    int cap;
    int flow;
    int rev;
};

struct InputEdge{
    int u,v,w,idx;
};

vector<vector<Edge>> g;
vector<InputEdge> inputEdges;

int n,m;

void addEdge(int u, int v, int c) {
    Edge forward = {v, c, 0, (int)g[v].size()};
    Edge backward = {u, 0, 0, (int)g[u].size()};
    
    g[u].push_back(forward);
    g[v].push_back(backward);
}


bool bfs(int s,int t, vector<pair<int,int>> &parent){
    fill(parent.begin(), parent.end(), make_pair(-1, -1));

    // for (int i = 0; i < parent.size(); i++) {
    //     parent[i].first = -1;
    //     parent[i].second = -1;
    // }

    queue<int> q;
    q.push(s);
    parent[s] = {s,-1};

    while(!q.empty()){
        int u = q.front();
        

        q.pop();
        for(int i=0;i<g[u].size();i++){
            Edge &e = g[u][i];

            if(parent[ e.v ].first == -1 && e.cap - e.flow > 0){
                parent[ e.v ] = {u,i};
                if(e.v == t) return true;
                q.push(e.v);
            }
        }
    }

    return false;
}

int edmondsKarp(int s,int t){
    int maxFlow = 0;
    vector< pair<int,int> > parent(g.size());

    while(bfs(s,t,parent)){
        int bottleneck = INT_MAX;

        for(int v = t; v != s; ){
            auto augmentEdge = parent[v];

            auto u = augmentEdge.first;
            auto idx = augmentEdge.second;

            bottleneck = min(bottleneck, g[u][idx].cap - g[u][idx].flow);
            v = u;
        }

        for(auto v = t; v != s; ){
            auto augmentEdge = parent[v];

            auto u = augmentEdge.first;
            auto idx = augmentEdge.second;

            g[u][idx].flow += bottleneck;
            g[v][ g[u][idx].rev ].flow -= bottleneck;

            v = u;
        }

        maxFlow += bottleneck;
    }

    return maxFlow;
}
int vin(int v){return v;}
int vout(int v){return v+n;}

int main(){
    cin>>n>>m;
    
    g.resize(2*n + 1);

    for(int i=1;i<=n;i++){
        if(i == 1 || i == n){
            addEdge(vin(i),vout(i),INF);
        }
        else{
            addEdge(vin(i),vout(i),1);
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(vout(u), vin(v), 1);
        inputEdges.push_back({u, v, 1, (int)g[u].size() - 1});
    }

    int maxFlow = edmondsKarp(vout(1),vin(n));
    cout<<maxFlow;

    return 0;
}