#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,ll>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    int src;
    cin >> src;

    vector<vector<ll>> dist(n, vector<ll>(2, INF));
    priority_queue<tuple<ll,int,int>,
        vector<tuple<ll,int,int>>,
        greater<>> pq;

    dist[src][0] = 0;
    pq.push({0, src, 0}); // (cost, node, coupon_used)

    while (!pq.empty()) {
        auto [d, u, used] = pq.top();
        pq.pop();

        if (d != dist[u][used]) continue;

        for (auto [v, w] : g[u]) {
            // normal edge
            if (dist[v][used] > d + w) {
                dist[v][used] = d + w;
                pq.push({dist[v][used], v, used});
            }

            // use coupon (only once)
            if (used == 0) {
                ll nw = max(0LL, w - 1); // coupon
                if (dist[v][1] > d + nw) {
                    dist[v][1] = d + nw;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    // result for each node
    for (int i = 0; i < n; i++) {
        ll ans = min(dist[i][0], dist[i][1]);
        if (ans == INF) cout << "INF\n";
        else cout << ans << "\n";
    }

    return 0;
}
