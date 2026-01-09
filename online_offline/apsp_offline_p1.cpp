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

int main(){
    ll m,n,q;
    cin>>n>>m>>q;

    vector< vector< pair<ll,ll> > > g(n+1);

    vector< vector<ll> > dist(n+1, vector<ll>(n+1,INF));

    for(int i=1;i<=n;i++){
        dist[i][i] = 0;
    }

    for(ll i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        g[u].push_back({v,w});
        g[v].push_back({u,w});
        
        dist[u][v] = min(dist[u][v],(ll)w);
        dist[v][u] = min(dist[u][v],(ll)w);
    }

    for(ll k=1;k<=n;k++){
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
                if((dist[i][j] > dist[i][k] + dist[k][j]) && 
                    dist[i][k] < INF && dist[k][j] < INF){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    vector<pair<ll,ll> > query;
    for(ll i=0;i<q;i++){
        ll u,v;
        cin>>u>>v;
        query.push_back({u,v});
    }

    for(auto co:query){
        ll u = co.first;
        ll v = co.second;
        if(dist[u][v] == INF) cout<<-1<<"\n";
        else cout<<dist[u][v]<<"\n";  
    }
    return 0;
}