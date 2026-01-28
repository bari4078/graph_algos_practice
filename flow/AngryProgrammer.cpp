#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v;
    int cap;
    int flow;
    int rev;
};

vector<vector<Edge>> g;

const int INF = 1e9;

void addEdge(int u, int v, int c) {
    Edge forward = {v, c, 0, (int)g[v].size()};
    Edge backward = {u, 0, 0, (int)g[u].size()};
    g[u].push_back(forward);
    g[v].push_back(backward);
}

bool bfs(int s, int t, vector<pair<int,int>> &parent) {
    fill(parent.begin(), parent.end(), make_pair(-1, -1));
    queue<int> q;
    q.push(s);
    parent[s] = {s, -1};

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            Edge &e = g[u][i];
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
    vector<pair<int,int>> parent(g.size());

    while (bfs(s, t, parent)) {
        int bottleneck = INT_MAX;

        for (int v = t; v != s; ) {
            auto [u, idx] = parent[v];
            bottleneck = min(bottleneck, g[u][idx].cap - g[u][idx].flow);
            v = u;
        }

        for (int v = t; v != s; ) {
            auto [u, idx] = parent[v];
            g[u][idx].flow += bottleneck;
            g[v][g[u][idx].rev].flow -= bottleneck;
            v = u;
        }

        maxFlow += bottleneck;
    }
    return maxFlow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;

        auto inNode  = [&](int x){ return 2 * x; };
        auto outNode = [&](int x){ return 2 * x + 1; };

        g.assign(2 * N + 5, vector<Edge>());

        // Node destruction costs (2 to N-1)
        for (int i = 2; i <= N - 1; i++) {
            int cost;
            cin >> cost;
            addEdge(inNode(i), outNode(i), cost);
        }

        // Source and sink (cannot be destroyed)
        addEdge(inNode(1), outNode(1), INF);
        addEdge(inNode(N), outNode(N), INF);

        // Cables
        for (int i = 0; i < M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            addEdge(outNode(u), inNode(v), w);
            addEdge(outNode(v), inNode(u), w);
        }

        int source = outNode(1);
        int sink   = inNode(N);

        cout << edmondsKarp(source, sink) << "\n";
    }
}
