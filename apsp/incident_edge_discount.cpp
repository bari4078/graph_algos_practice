#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX / 2;

int main() {
    ll n, m;
    cin >> n >> m;
    ll V;
    cin >> V;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));

    // initialize self-distances
    for(int i = 0; i < n; i++) dist[i][i] = 0;

    vector<vector<pair<ll,ll>>> g(n+1); // store edges temporarily
    for(int i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        ll cost = w;
        if(u == V or v == V) cost = w-1;
        dist[u][v] = min(dist[u][v],cost);
    }


    // Floyd–Warshall
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if(dist[i][k] == INF) continue;
            for(int j = 0; j < n; j++){
                if(dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    ll q;
    cin >> q;
    while(q--){
        ll u,d;
        cin >> u >> d;
        if(dist[u][d] == INF) cout << -1 << "\n";
        else cout << dist[u][d] << "\n";
    }

    return 0;
}
