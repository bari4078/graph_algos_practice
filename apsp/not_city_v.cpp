#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));

    // distance to itself = 0
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }

    // read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // directed graph
    }

    int V; // city that must NOT be passed through
    cin >> V;

    // Floyd–Warshall
    for (int k = 1; k <= n; k++) {

        // 🚫 do NOT allow paths to go through V
        if (k == V) continue;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // output APSP matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] >= INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
