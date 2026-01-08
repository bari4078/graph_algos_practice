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
    vector< ll> dist(n+1,0);

    for(ll i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    ll negCycle = -1;

    vector<ll> cyclePar(n+1,-1);

    for(ll i=0;i<n;i++){
        negCycle = -1;

        for(ll j=1; j<n+1;j++){
            for(auto [v,w]: g[j]){
                if((dist[j] + w < dist[v])){
                    dist[v] = dist[j] + w;
                    cyclePar[v] = j;
                    negCycle = v;
                }
            }
        }
    }

    if(negCycle == -1){
        cout<<negCycle;
        //cout<<"NO";
    }
    else{
        //cout<<"YES\n";
        ll curr = negCycle;

        for(ll i=0;i<n;i++){
            curr = cyclePar[curr];
        }

        ll start = curr;
        vector<ll> res;

        do{
            res.push_back(curr);
            curr = cyclePar[curr];
        }while(curr != start);
        //res.push_back(start);

        reverse(res.begin(),res.end());

        for(ll u: res){
            cout<<u<<" ";
        }
    }

    return 0;
}