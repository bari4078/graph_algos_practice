#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;


int main(){
int n, m, k, V;
cin >> n >> m >> V >> k;

vector<vector<ll>> g(n, vector<ll>(n, INF));
for (int i = 0; i < n; i++) g[i][i] = 0;

for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u][v] = min(g[u][v], (ll)w);
}

// 3D DP: dist[u][v][d] = shortest distance u->v with d discounted edges left
vector<vector<vector<ll>>> dist(n, vector<vector<ll>>(n, vector<ll>(k+1, INF)));

// Initial distances: from i to i, discount 0
for (int i = 0; i < n; i++) dist[i][i][0] = 0;

// Floyd-Warshall with discount states
for (int mid = 0; mid < n; mid++) {
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            for (int d = 0; d <= k; d++) {
                if (dist[u][mid][d] == INF) continue;

                // if we go from mid -> v
                for (int dd = 0; dd <= k; dd++) {
                    if (dist[mid][v][dd] == INF) continue;

                    ll cost = dist[mid][v][dd];
                    if (d > 0) cost = cost - 1;  // apply discount

                    int new_d = (mid == V ? k : max(d-1, 0));
                    dist[u][v][new_d] = min(dist[u][v][new_d], dist[u][mid][d] + cost);
                }
            }
        }
    }
}

// Extract final answer
for (int u = 0; u < n; u++) {
    for (int v = 0; v < n; v++) {
        ll ans = INF;
        for (int d = 0; d <= k; d++) ans = min(ans, dist[u][v][d]);
        cout << ans << " ";
    }
    cout << "\n";
}
}
