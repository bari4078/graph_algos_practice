#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));

    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // directed
    }

    int V;
    cin >> V;

    // Floyd–Warshall WITHOUT allowing V as intermediate
    for (int k = 1; k <= n; k++) {
        if (k == V) continue;   // 🔒 prevents revisiting V
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Final APSP: must pass through V exactly once
    vector<vector<ll>> ans(n + 1, vector<ll>(n + 1, INF));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][V] < INF && dist[V][j] < INF) {
                ans[i][j] = dist[i][V] + dist[V][j];
            }
        }
    }

    // Output
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ans[i][j] >= INF) cout << "INF ";
            else cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
