#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <climits>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

vector< vector<ll> > dist;
int main(){
    ll n,m,q;
    cin>>n>>m>>q;

    dist.assign(n+1, vector<ll>(n+1,INF));

    for(ll i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        dist[u][v] = min(dist[u][v],w);
        dist[v][u] = min(dist[u][v],w);
    }

    for(int i=1;i<=n;i++){
        dist[i][i] = 0;
    }

    for(ll k=1;k<=n;k++){
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    vector<pair<ll,ll>> query;
    for(ll i=0;i<q;i++){
        ll u,v;
        cin>>u>>v;
        query.push_back({u,v});
    }

    for(auto [u,v]:query){
        if(dist[u][v] == INF){
            cout<<-1<<'\n';
        }
        else{
            cout<<dist[u][v]<<'\n';
        }
    }
    return 0;
}