#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v;
    int cap;
    int flow;
    int rev;
};

struct InputEdge{
    int u, v, L, U, idx;
};

vector<vector<Edge>> g;
vector<InputEdge> inputEdges;
vector<int> demand;

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
        int u = q.front(); q.pop();
        for(int i=0;i<g[u].size();i++){
            Edge &e = g[u][i];
            if(parent[e.v].first == -1 && e.cap - e.flow > 0){
                parent[e.v] = {u,i};
                if(e.v == t) return true;
                q.push(e.v);
            }
        }
    }
    return false;
}

int edmondsKarp(int s,int t){
    int maxFlow = 0;
    vector<pair<int,int>> parent(g.size());

    while(bfs(s,t,parent)){
        int bottleneck = INT_MAX;
        for(int v = t; v != s; ){
            auto [u, idx] = parent[v];
            bottleneck = min(bottleneck, g[u][idx].cap - g[u][idx].flow);
            v = u;
        }

        for(int v = t; v != s; ){
            auto [u, idx] = parent[v];
            g[u][idx].flow += bottleneck;
            g[v][ g[u][idx].rev ].flow -= bottleneck;
            v = u;
        }

        maxFlow += bottleneck;
    }
    return maxFlow;
}

int main(){
    int n, m;
    cin >> n >> m;

    int S, T;
    cin >> S >> T;

    int SS = n;
    int TT = n + 1;

    g.assign(n + 2, {});
    demand.assign(n + 2, 0);

    for(int i = 0; i < m; i++){
        int u, v, L, U;
        cin >> u >> v >> L >> U;

        addEdge(u, v, U - L);
        inputEdges.push_back({u, v, L, U, (int)g[u].size() - 1});

        demand[u] -= L;
        demand[v] += L;
    }

    int need = 0;
    for(int i = 0; i < n; i++){
        if(demand[i] > 0){
            addEdge(SS, i, demand[i]);
            need += demand[i];
        }
        else if(demand[i] < 0){
            addEdge(i, TT, -demand[i]);
        }
    }

    const int INF = 1e9;
    addEdge(T, S, INF);

    int flow = edmondsKarp(SS, TT);

    if(flow != need){
        cout << "NO\n";
        return 0;
    }

    // Feasible → now compute max S → T
    int extra = 0;
    for(auto &e : inputEdges){
        if(e.u == S) extra += e.L;
    }

    int maxST = edmondsKarp(S, T);
    cout << "YES\n";
    cout << "Max Flow = " << maxST + extra << "\n";

    // Print actual flows
    for(auto &e : inputEdges){
        Edge &ed = g[e.u][e.idx];
        int realFlow = ed.flow + e.L;
        cout << e.u << " " << e.v << " " << realFlow << "/" << e.U << "\n";
    }
}
