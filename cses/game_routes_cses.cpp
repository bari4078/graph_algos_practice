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
const ll MOD = 1e9 + 7;

vector< vector<ll> > g;
vector<ll> dp;
vector<bool> vis;
ll n,m;


int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin>>n>>m;

    g.resize(n+1);
    dp.assign(n+1,0);
    vis.assign(n+1,false);
    vector<ll> inDeg(n+1,0);

    for(ll i=0;i<m;i++){
        ll u,v;
        cin>>u>>v;
        g[u].push_back(v);
        inDeg[v]++;
    }
    
    vector<ll> topo;
    queue<ll> q;

    for(int i=1;i<=n;i++){
        if(inDeg[i] == 0) q.push(i);
    }

    while(!q.empty()){
        auto u = q.front(); q.pop();
        topo.push_back(u);
        for(auto v:g[u]){
            inDeg[v]--;
            if(inDeg[v] == 0){
                q.push(v);
            }
        }
    }
    dp[1] = 1;
    for(auto u:topo){
        for(auto v:g[u]){
            dp[v] = (dp[v] + dp[u]) % MOD;
        }
    }
    cout<<dp[n];
    return 0;
}