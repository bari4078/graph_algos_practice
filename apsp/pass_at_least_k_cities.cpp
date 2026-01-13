#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX / 4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for(int i = 0; i < n; i++) dist[i][i] = 0;

    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // undirected; remove second line if directed
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // special cities
    int s, k;
    cin >> s >> k;
    vector<int> special(s);
    for(int i = 0; i < s; i++) cin >> special[i];

    // Floyd–Warshall
    for(int mid = 0; mid < n; mid++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[i][mid] + dist[mid][j] < dist[i][j]){
                    dist[i][j] = dist[i][mid] + dist[mid][j];
                }
            }
        }
    }

    int q;
    cin >> q;

    while(q--){
        int u, v;
        cin >> u >> v;

        int S = 1 << s;
        vector<vector<ll>> dp(S, vector<ll>(s, INF));

        // init
        for(int i = 0; i < s; i++){
            if(dist[u][special[i]] < INF){
                dp[1 << i][i] = dist[u][special[i]];
            }
        }

        // subset DP
        for(int mask = 0; mask < S; mask++){
            for(int i = 0; i < s; i++){
                if(!(mask & (1 << i))) continue;
                if(dp[mask][i] == INF) continue;

                for(int j = 0; j < s; j++){
                    if(mask & (1 << j)) continue;
                    ll nd = dp[mask][i] + dist[special[i]][special[j]];
                    dp[mask | (1 << j)][j] =
                        min(dp[mask | (1 << j)][j], nd);
                }
            }
        }

        ll ans = INF;

        for(int mask = 0; mask < S; mask++){
            if(__builtin_popcount(mask) < k) continue;
            for(int i = 0; i < s; i++){
                if(!(mask & (1 << i))) continue;
                if(dp[mask][i] == INF) continue;
                if(dist[special[i]][v] == INF) continue;
                ans = min(ans, dp[mask][i] + dist[special[i]][v]);
            }
        }

        if(ans == INF) cout << -1 << '\n';
        else cout << ans << '\n';
    }

    return 0;
}
