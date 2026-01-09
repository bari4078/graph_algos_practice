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
    vector<ll> res;
    for(int i=1;i<=n;i++){
        if(inDeg[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        res.push_back(u);
        for(auto v:g[u]){
            inDeg[v]--;
            if(inDeg[v] == 0) q.push(v);
        }
    }

    if(res.size() < n){
        cout<<"IMPOSSIBLE";
        return 0;
    }

    for(auto u:res){
        cout<<u<<' ';
    }
    return 0;
}