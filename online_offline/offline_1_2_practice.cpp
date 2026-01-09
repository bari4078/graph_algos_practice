#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <climits>

using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int main(){
    ll n,m;
    cin>>n>>m;

    vector< vector< pair<ll,ll> > > g(n+1);
    vector<ll> dist(n+1,0);

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    ll negCycle = -1;
    vector<ll> par(n+1,-1);

    for(int i=0;i<=n;i++){
        negCycle = -1;
        for(int j =1;j<=n;j++){
            for(auto [v,w]:g[j]){
                if(dist[v] > dist[j] + w)
                {
                    dist[v] = dist[j] + w;
                    par[v] = j;
                    negCycle = v;
                }
            }
        }
    }

    if(negCycle == -1){
        cout<<"NO";
        return 0;
    }

    int curr = negCycle;
    for(int i=0;i<n;i++){
        curr = par[curr];
    }

    vector<ll> cycle;

    cycle.push_back(curr);
    curr = par[curr];
    while(curr != cycle[0]){
        cycle.push_back(curr);
        curr = par[curr];
    }
    cycle.push_back(cycle[0]);
    reverse(cycle.begin(),cycle.end());

    cout<<"YES"<<'\n';
    for(auto v: cycle){
        cout<<v<<' ';
    }
    return 0;
}