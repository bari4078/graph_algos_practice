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
    vector< vector<pair<ll,ll> > > rg(n+1);

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        rg[v].push_back({u,w});
    }

    ll x,y,z;
    cin>>x>>y>>z;

    vector< vector<ll> > d1toX(n+1, vector<ll>(2,INF));

    priority_queue<
                    pair< ll, pair<ll,ll> >,
                    vector < pair< ll, pair<ll,ll> > >,
                    greater< pair< ll, pair<ll,ll> > >
                    > pq;
    d1toX[1][0] = 0;
    pq.push({d1toX[1][0],{1,0}});

    while(!pq.empty()){
        auto d = pq.top().first;
        auto u = pq.top().second.first;
        auto state = pq.top().second.second;
        pq.pop();
        if(d > d1toX[u][state]) continue;

        if(state == 1 ){
            for(auto [v,w]: g[u]){
                if(d1toX[v][1] > d1toX[u][1] + w){
                    d1toX[v][1] = d1toX[u][1] + w;
                    pq.push({d1toX[v][1],{v,1}});
                }
            }
        }

        else if(state == 0){
            for(auto [v,w]: g[u]){
                if(d1toX[v][1] > d1toX[u][0] + w/2){
                    d1toX[v][1] = d1toX[u][0] + w/2;
                    pq.push({d1toX[v][1],{v,1}});
                }
                if(d1toX[v][0] > d1toX[u][0] + w){
                    d1toX[v][0] = d1toX[u][0] + w;
                    pq.push({d1toX[v][0],{v,0}});
                }
            }
        }
    }
    while(!pq.empty()) pq.pop();
    
    vector< vector<ll> > dNtoY(n+1, vector<ll>(2,INF));

    dNtoY[n][0] = 0;
    pq.push({dNtoY[n][0],{n,0}});

    while(!pq.empty()){
        auto d = pq.top().first;
        auto u = pq.top().second.first;
        auto state = pq.top().second.second;
        pq.pop();
        if(d > dNtoY[u][state]) continue;

        if(state == 1 ){
            for(auto [v,w]: rg[u]){
                if(dNtoY[v][1] > dNtoY[u][1] + w){
                    dNtoY[v][1] = dNtoY[u][1] + w;
                    pq.push({dNtoY[v][1],{v,1}});
                }
            }
        }

        else if(state == 0){
            for(auto [v,w]: rg[u]){
                if(dNtoY[v][1] > dNtoY[u][0] + w/2){
                    dNtoY[v][1] = dNtoY[u][0] + w/2;
                    pq.push({dNtoY[v][1],{v,1}});
                }
                if(dNtoY[v][0] > dNtoY[u][0] + w){
                    dNtoY[v][0] = dNtoY[u][0] + w;
                    pq.push({dNtoY[v][0],{v,0}});
                }
            }
        }
    }

    ll cost = min(d1toX[x][1] + z + dNtoY[y][0],
                min(
                    d1toX[x][0] + z + dNtoY[y][1],
                    d1toX[x][0] + z/2 + dNtoY[y][0]
                ));
    
    if(cost == INF) cout<<"Not possible";
    else cout<<cost;
    return 0;
    
}