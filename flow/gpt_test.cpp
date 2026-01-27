#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, cap, flow, rev;
};

struct InputEdge {
    int u, v, c, idx;
};

vector<vector<Edge>> adj;
vector<InputEdge> inputEdges;

void addEdge(int u, int v, int c) {
    Edge a = {v, c, 0, (int)adj[v].size()};
    Edge b = {u, 0, 0, (int)adj[u].size()};
    adj[u].push_back(a);
    adj[v].push_back(b);
}

bool bfs(int s, int t, vector<pair<int,int>>& parent) {
    fill(parent.begin(), parent.end(), make_pair(-1, -1));
    queue<int> q;
    q.push(s);
    parent[s] = {s, -1};

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (parent[e.v].first == -1 && e.cap - e.flow > 0) {
                parent[e.v] = {u, i};
                if (e.v == t) return true;
                q.push(e.v);
            }
        }
    }
    return false;
}

int edmondsKarp(int s, int t) {
    int maxFlow = 0;
    vector<pair<int,int>> parent(adj.size());

    while (bfs(s, t, parent)) {
        int pathFlow = INT_MAX;

        for (int v = t; v != s; ) {
            auto e = parent[v];
            auto u = e.first;
            auto idx = e.second;
            
            pathFlow = min(pathFlow, adj[u][idx].cap - adj[u][idx].flow);
            v = u;
        }

        for (int v = t; v != s; ) {
            auto e = parent[v];
            auto u = e.first;
            auto idx = e.second;
            
            adj[u][idx].flow += pathFlow;
            adj[v][adj[u][idx].rev].flow -= pathFlow;
            v = u;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    int N, M;
    cin >> N >> M;
    adj.assign(N, {});

    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
        inputEdges.push_back({u, v, c, (int)adj[u].size() - 1});
    }

    int s, t;
    cin >> s >> t;

    int maxFlow = edmondsKarp(s, t);
    cout << maxFlow << "\n";

    for (auto &e : inputEdges) {
        Edge &ed = adj[e.u][e.idx];
        cout << e.u << " " << e.v << " "
             << ed.flow << "/" << e.c << "\n";
    }
}
