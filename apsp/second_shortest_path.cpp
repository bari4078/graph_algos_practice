#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> d1(n, vector<ll>(n, INF));
    vector<vector<ll>> d2(n, vector<ll>(n, INF));

    // init
    for (int i = 0; i < n; i++) {
        d1[i][i] = 0;
    }

    // input edges
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        if (w < d1[u][v]) {
            d2[u][v] = d1[u][v];
            d1[u][v] = w;
        } else if (w > d1[u][v] && w < d2[u][v]) {
            d2[u][v] = w;
        }
    }

    // Floyd–Warshall for 2 shortest paths
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (d1[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (d1[k][j] == INF) continue;

                ll cand = d1[i][k] + d1[k][j];

                if (cand < d1[i][j]) {
                    d2[i][j] = d1[i][j];
                    d1[i][j] = cand;
                } 
                else if (cand > d1[i][j] && cand < d2[i][j]) {
                    d2[i][j] = cand;
                }
            }
        }
    }

    // query example
    int u, v;
    cin >> u >> v;

    if (d2[u][v] == INF) {
        cout << "No second shortest path\n";
    } else {
        cout << "Shortest: " << d1[u][v] << "\n";
        cout << "Second shortest: " << d2[u][v] << "\n";
    }

    return 0;
}
