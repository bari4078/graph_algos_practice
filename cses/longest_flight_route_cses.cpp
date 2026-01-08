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
    ios::sync_with_stdio(0); cin.tie(0);

    ll n,m;
    cin>>n>>m;

    vector< vector<ll> > g(n+1);
    vector<int> inDeg(n+1,0);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        inDeg[v]++;
    }

    queue<ll> q;
    vector<ll> topo;
    for(int i=1;i<=n;i++){
        if(inDeg[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        topo.push_back(u);
        for(auto v:g[u]){
            inDeg[v]--;
            if(inDeg[v] == 0) q.push(v);
        }
    }

    vector<ll> dist(n+1,-1);
    dist[1] = 1;        
    vector<ll> par(n+1,-1);
    for(auto u:topo){
        for(auto v:g[u]){
            if(dist[u] != -1 && dist[v] < dist[u] + 1){
                par[v] = u;
                dist[v] = dist[u] + 1;
            }
        }
    }

    if(dist[n] == -1){
        cout<<"IMPOSSIBLE";
        return 0;
    }
    
    vector<ll> path;
    ll curr = n;
    while(curr != 1){
        path.push_back(curr);
        curr = par[curr];
    }
    path.push_back(1);
    reverse(path.begin(),path.end());
    cout<<path.size()<<'\n';
    for(auto u:path){
        cout<<u<<' ';
    }
    return 0;
}