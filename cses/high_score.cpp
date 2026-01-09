#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <climits>
using namespace std;

using ll = long long;
const ll MIN = LLONG_MIN/2;

int main(){
    ll n,m;
    cin>>n>>m;

    vector< tuple<ll,ll,ll> > edges;
    vector<ll> dist(n+1,MIN);

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }
    dist[1] = 0;
    for(int i=1;i<=n-1;i++){
        for(auto [u,v,w]:edges){
            if(dist[u] != MIN && dist[u] + w > dist[v]){
                dist[v] = dist[u] + w;
            }
        }
    }
    
    vector< vector<ll> > rg(n+1);
    vector<bool> reach(n+1,false);
    for(auto [u,v,w]:edges){
        rg[v].push_back(u);
    }

    reach[n] = true;
    queue<ll> q;
    q.push(n);

    while(!q.empty()){
        auto u = q.front(); q.pop();
        for(auto v:rg[u]){
            if(!reach[v]){
                reach[v] = true;
                q.push(v);
            }
        }
    }

    for(auto [u,v,w]:edges){
        if(dist[u] != MIN && (dist[u] + w > dist[v]) && reach[v]){
            cout<<-1;
            return 0;
        }
    }
    cout<<dist[n];
    return 0;
}