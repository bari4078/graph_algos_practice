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
    int count = 1;
    while(true){
        ll n,m,q;
        cin>>n>>m>>q;

        if(n == 0 && m == 0 && q == 0) break;

        vector< vector< ll > > dist(n+1,vector<ll>(n+1,INF));

        for(int i=0;i<m;i++){
            ll u,v,w;
            cin>>u>>v>>w;
            dist[u][v] = min(dist[u][v],w);
            dist[v][u] = min(dist[v][u],w);
        }
        for(int i=1;i<=n;i++) dist[i][i] = 0;
        for(int k = 1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(dist[i][k] != INF && dist[k][j] != INF
                        && dist[i][j] > max(dist[i][k],dist[k][j])){
                            dist[i][j] = max(dist[i][k],dist[k][j]);
                        }
                }
            }
        }

        cout<<"Case #"<<count++<<"\n";
        for(int i=0;i<q;i++){
            int u,v;
            cin>>u>>v;
            if(dist[u][v] == INF) cout<<"no path\n";
            else cout<<dist[u][v]<<"\n";
        }
        //cout << "\n";
    }

}