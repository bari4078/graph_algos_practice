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

    ll n,m,k;
    cin>>n>>m>>k;

    vector< vector< pair<ll,ll> > > g(n+1);

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    priority_queue< pair <ll, ll>,
                    vector< pair <ll,ll> >,
                    greater< pair<ll,ll> >
                > pq;

    vector<ll> results;
    vector<ll> count(n+1,0);

    pq.push({0,1});

    while(!pq.empty() && count[n] < k){
        ll d = pq.top().first;
        ll u = pq.top().second;

        pq.pop();
        count[u]++;

        if( u== n){
            results.push_back(d);
        }

        if(count[u] > k) continue;
        
        for(auto &edge : g[u]){
            ll v = edge.first;
            ll w = edge.second;

            if(count[v] < k){
                pq.push({d+w,v});
            }
        }
    }

    for(auto d: results){
        cout<<d<<' ';
    }
    return 0;
}