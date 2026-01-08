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

void dfs(vector< vector<ll> > &g,
        vector<bool> &vis,
        int s){
    vis[s] = true;

    for(int v: g[s]){
        if(!vis[v]){
            dfs(g,vis,v);
        }
    }
}

int main(){
    ll n,m;
    cin>>n>>m;

    vector< vector <ll> > g(n+1);

    for(ll i=0; i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<bool> vis(n+1,false);

    vector<ll> start_comp;
    ll comp_count = 0;

    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            comp_count++; 
            dfs(g,vis,i);
            start_comp.push_back(i);
        }
    }

    cout<<comp_count -1<<'\n';
    
    for(int i=0;i<start_comp.size()-1;i++){
        cout<<start_comp[i]<<' '<<start_comp[i+1]<<'\n';
    }
    return 0;
}