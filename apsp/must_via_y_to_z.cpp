#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <map>
#include <string>
#include <climits>
#include <set>
#include <iomanip>

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;


int main(){
    ll n,m;
    cin>>n>>m;

    vector<vector<ll>> dist(n+1,vector<ll>(n+1,INF));

    for(int i=0;i<n;i++){
        dist[i][i] = 0;
    }

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;   
        dist[u][v] = min(w,dist[u][v]);
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    ll y,z;
    cin>>y>>z;

    vector<vector<ll>> ans(n+1,vector<ll>(n+1,INF));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dist[i][y] == INF || dist[y][z] == INF 
                || dist[z][j] == INF) continue;

            ans[i][j] = dist[i][y] + dist[y][z] + dist[z][j];
        }
    }

    ll q;
    cin>>q;

    for(int i=0;i<q;i++){
        ll u,d;
        cin>>u>>d;
        if(ans[u][d] == INF) cout<<"INF"<<'\n';
        else cout<<ans[u][d] << '\n';
    }
}