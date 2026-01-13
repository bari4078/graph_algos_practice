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
    vector<vector<ll>> distDiscount(n+1,vector<ll>(n+1,INF));

    for(int i=0;i<n;i++){
        dist[i][i] = 0;
        distDiscount[i][i] = 0;
    }

    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;   
        dist[u][v] = min(w,dist[u][v]);

        distDiscount[u][v] = min(w-1,distDiscount[u][v]);
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
    ll v;
    cin>>v;

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(distDiscount[i][j] > distDiscount[i][k] + distDiscount[k][j]){
                    distDiscount[i][j] = distDiscount[i][k] + distDiscount[k][j];
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dist[i][j] = min(
                dist[i][j],
                distDiscount[i][v] + distDiscount[v][j]
            );
        }
    }

    ll q;
    cin>>q;

    for(int i=0;i<q;i++){
        ll u,d;
        cin>>u>>d;
        if(dist[u][d] == INF) cout<<-1<<'\n';
        else cout<<dist[u][d] << '\n';
    }

    return 0;
}