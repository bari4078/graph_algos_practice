#include <bits/stdc++.h>
using namespace std;

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

void addEdge(int u, int v, int c) {
    Edge forward = {v, c, 0, (int)g[v].size()};
    Edge backward = {u, 0, 0, (int)g[u].size()};
    
    g[u].push_back(forward);
    g[v].push_back(backward);
}

bool bfs(int s,int t, vector<pair<int,int>> &parent){
    fill(parent.begin(), parent.end(), make_pair(-1, -1));

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

int main(){
    int n,m;
    cin>>n>>m;
    
    g.resize(n + 100);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
        inputEdges.push_back({u, v, w, (int)g[u].size() - 1});
    }

    int s,t;
    cin>>s>>t;

    int maxFlow = edmondsKarp(s,t);
    cout << maxFlow << "\n";

    for(auto &e:inputEdges){
        Edge og = g[ e.u ][e.idx];
        cout << e.u << " " << e.v << " " << og.flow << "/" << e.w << "\n";
    }

    // ---- Find min cut ----
    vector<int> visS(g.size(), 0);
    queue<int> q;
    q.push(s);
    visS[s] = 1;

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &e : g[u]){
            if(!visS[e.v] && e.cap - e.flow > 0){
                visS[e.v] = 1;
                q.push(e.v);
            }
        }
    }

    cout << "One min cut edges:\n";
    for(auto &e : inputEdges){
        if(visS[e.u] && !visS[e.v]){
            cout << e.u << " " << e.v << "\n";
        }
    }

    // ---- Check uniqueness ----
    bool unique = true;
    for(int u = 0; u < g.size(); u++){
        if(!visS[u]){
            for(auto &e : g[u]){
                if(visS[e.v] && e.cap - e.flow > 0){
                    unique = false;
                }
            }
        }
    }
    cout << (unique ? "Unique min cut\n" : "Multiple min cuts\n");

    // ---- Find all edges that appear in some min cut ----
    vector<int> visT(g.size(), 0);
    queue<int> q2;
    q2.push(t);
    visT[t] = 1;

    while(!q2.empty()){
        int u = q2.front(); q2.pop();
        for(auto &e : g[u]){
            Edge &rev = g[e.v][e.rev];
            if(!visT[e.v] && rev.cap - rev.flow > 0){
                visT[e.v] = 1;
                q2.push(e.v);
            }
        }
    }

    cout << "Edges in some min cut:\n";
    for(auto &e : inputEdges){
        if(visS[e.u] && visT[e.v]){
            cout << e.u << " " << e.v << "\n";
        }
    }
}
