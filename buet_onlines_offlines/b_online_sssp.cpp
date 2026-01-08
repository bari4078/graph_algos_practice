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

    vector< vector< pair<ll,ll> > > g(n+1);

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    vector< vector<ll> > dist(n+1, vector<ll>(3,INF));

    priority_queue<
                    pair< ll, pair<ll,ll> >,
                    vector < pair< ll, pair<ll,ll> > >,
                    greater< pair< ll, pair<ll,ll> > >
                    > pq;
    dist[1][0] = 0;
    pq.push({dist[1][0],{1,0}});

    while(!pq.empty()){
        auto d = pq.top().first;
        auto u = pq.top().second.first;
        auto state = pq.top().second.second;
        pq.pop();
        if(d > dist[u][state]) continue;

        if(state == 0){
            for(auto[v,w]:g[u]){
                if(dist[v][0] > dist[u][0] + w){
                    dist[v][0] = dist[u][0] + w;
                    pq.push({dist[v][0],{v,0}});
                }
                if(dist[v][1] > dist[u][0] + w/2){
                    dist[v][1] = dist[u][0] + w/2;
                    pq.push({dist[v][1],{v,1}});
                }
            }
        }
        if(state == 1){
            for(auto[v,w]:g[u]){
                if(dist[v][1] > dist[u][1] + w){
                    dist[v][1] = dist[u][1] + w;
                    pq.push({dist[v][1],{v,1}});
                }
                if(dist[v][2] > dist[u][1] + w/2){
                    dist[v][2] = dist[u][1] + w/2;
                    pq.push({dist[v][2],{v,2}});
                }
            }
        }
        if(state == 2){
            for(auto[v,w]:g[u]){
                if(dist[v][2] > dist[u][2] + w){
                    dist[v][2] = dist[u][2] + w;
                    pq.push({dist[v][2],{v,2}});
                } 
            }
        }
    }

    cout<<dist[n][2];
}