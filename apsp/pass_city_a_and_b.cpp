#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <map>
#include <string>
#include <climits>
#include <set>
#include <iomanip>

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main(){
    ll n,m;
    cin>>n>>m;

    vector<vector<ll>> dist(n+1,vector<ll>(n+1,INF));
    for(int i=0;i<n;i++) dist[i][i] = 0;

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;   
        dist[u][v] = min(w,dist[u][v]);
        dist[v][u] = min(w,dist[v][u]);
    }
    ll y,z;
    cin>>y>>z;

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    ll q;
    cin>>q;
    vector< pair<ll,ll> > query;

    for(int i=0;i<q;i++){
        ll u,v;
        cin>>u>>v;
        ll ans = INF;

        if(dist[u][y] < INF && dist[y][z] < INF && dist[z][v] < INF){
            ans = dist[u][y] + dist[y][z] + dist[z][v];
        }

        if(dist[u][z] < INF && dist[z][y] < INF && dist[y][v] < INF){
            ans = min(ans, dist[u][z] + dist[z][y] + dist[y][v]);
        }

        if(ans == INF) cout << -1 << '\n';
        else cout << ans << '\n';

    }

    return 0;
}