 #include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main() {
    ll n,m;
    cin >> n >> m;

    vector<vector<vector<ll>>> dist(n, vector<vector<ll>>(n, vector<ll>(2, INF)));

    // initialize self-distances
    for(int i=0;i<n;i++) dist[i][i][0] = dist[i][i][1] = 0;

    vector<vector<pair<ll,ll>>> g(n);
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
    }

    ll V;
    cin >> V;

    // Floyd–Warshall with states
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int s=0;s<2;s++){ // current state
                    if(dist[i][k][s] == INF) continue;
                    for(auto &edge: g[k]){
                        ll next = edge.first;
                        ll w = edge.second;

                        ll new_state = s;
                        ll cost = w;

                        if(s == 1 || k == V) { // discount applies after visiting V
                            new_state = 1;
                            cost = w-1;
                        }

                        if(dist[i][next][new_state] > dist[i][k][s] + cost){
                            dist[i][next][new_state] = dist[i][k][s] + cost;
                        }
                    }
                }
            }
        }
    }

    ll q;
    cin >> q;
    while(q--){
        ll u,d;
        cin >> u >> d;
        ll ans = min(dist[u][d][0], dist[u][d][1]);
        if(ans >= INF) cout << -1 << "\n";
        else cout << ans << "\n";
    }

    return 0;
}
