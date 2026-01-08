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

vector<ll> cycle;

void dfs(vector< vector<ll> > &g,
        vector< int> &state,
        vector<ll> &par,
        int s){
            if(!cycle.empty()) return;
            state[s] = 1;

            for(auto v : g[s]){
                if(state[v] == 0){
                    par[v] = s;
                    dfs(g,state,par,v);

                    if(!cycle.empty()) return;
                }
                else if(state[v] == 1){
                    cycle.push_back(v);
                    ll curr = s;
                    while(curr != v){
                        cycle.push_back(curr);
                        curr = par[curr];
                    }
                    cycle.push_back(v);
                    return;
                }
            }
            state[s] = 2;
        }


int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    ll n,m;
    cin>>n>>m;

    vector< vector<ll> > g(n+1);
    vector< int> state(n+1,0);
    vector<ll> par(n+1,-1);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }

    for(int i=1;i<=n;i++){
        if(state[i] == 0) dfs(g,state,par,i);
        if(!cycle.empty()) break;
    }

    if(cycle.empty()){
        cout<<"IMPOSSIBLE";
    }
    else{
        cout<<cycle.size()<<'\n';
        reverse(cycle.begin(),cycle.end());
        for(auto v:cycle){
            cout<<v<<' ';
        }
    }
    return 0;
}