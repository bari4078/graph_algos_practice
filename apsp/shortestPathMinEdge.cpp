#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const long long LINF = 1e18;

struct State {
    int edges;
    long long weight;
};

bool better(const State& a, const State& b) {
    if (a.edges != b.edges) return a.edges < b.edges;
    return a.weight < b.weight;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<State>> dist(n + 1, vector<State>(n + 1, {INF, LINF}));

    // self
    for (int i = 1; i <= n; i++) {
        dist[i][i] = {0, 0};
    }

    // edges
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], {1, w},
                         [](auto a, auto b) {
                             if (a.edges != b.edges) return a.edges < b.edges;
                             return a.weight < b.weight;
                         });
    }

    // Floyd–Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k].edges == INF || dist[k][j].edges == INF) continue;

                State cand = {
                    dist[i][k].edges + dist[k][j].edges,
                    dist[i][k].weight + dist[k][j].weight
                };

                if (better(cand, dist[i][j])) {
                    dist[i][j] = cand;
                }
            }
        }
    }

    // output
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j].edges == INF)
                cout << "NO_PATH ";
            else
                cout << "(" << dist[i][j].edges << "," << dist[i][j].weight << ") ";
        }
        cout << "\n";
    }

    return 0;
}
