#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG_INF = -1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, NEG_INF));

    // distance to itself
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }

    // edges
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v] = max(dist[u][v], w); // directed
    }

    // Floyd–Warshall (MAX)
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] == NEG_INF || dist[k][j] == NEG_INF) continue;
                dist[i][j] = max(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // output
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == NEG_INF) cout << "NO_PATH ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
