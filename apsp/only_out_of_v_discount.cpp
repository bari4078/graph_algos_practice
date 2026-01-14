#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main() {
    ll n, m;
    cin >> n >> m;

    vector<vector<pair<ll,ll>>> g(n); // adjacency list
    for(int i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    ll V;
    cin >> V;

    // 2D distance arrays: dist[node][state]
    vector<vector<ll>> dist(n, vector<ll>(2, INF));

    // initialize self-distances
    for(int i = 0; i < n; i++) dist[i][0] = dist[i][1] = 0;

    // Floyd–Warshall with states
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int s = 0; s < 2; s++){ // current state
                if(dist[i][s] == INF) continue;
                for(auto e : g[k]){
                    auto next_ver = e.first;
                    auto w = e.second;

                    ll new_state = s;
                    ll cost = w;

                    // only first edge after V gets discount
                    if(k == V && s == 0){
                        cost = w - 1;
                        new_state = 1; // discount used
                    }

                    if(dist[next_ver][new_state] > dist[i][s] + cost){
                        dist[next_ver][new_state] = dist[i][s] + cost;
                    }
                }
            }
        }
    }

    ll q;
    cin >> q;
    while(q--){
        ll u, d;
        cin >> u >> d;
        ll ans = min(dist[d][0], dist[d][1]);
        if(ans >= INF) cout << -1 << "\n";
        else cout << ans << "\n";
    }

    return 0;
}
