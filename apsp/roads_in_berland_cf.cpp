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

ll show_sum(vector<vector<ll> > &dist,int n){
    ll sum = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            sum += dist[i][j];
        }
    }
    return sum;
}

int main(){
    ll n;
    cin>>n;

    vector< vector<ll> > dist(n+1,vector<ll>(n+1));

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ll d;
            cin>>d;
            dist[i][j] = d;
        }
    }

    ll k;
    cin>>k;

    for(int i=0;i<k;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        dist[u][v] = min(dist[u][v],w);
        dist[v][u] = min(dist[v][u],w);

        for(int x=1;x<=n;x++){
            for(int y=1;y<=n;y++){
                dist[x][y] = min(dist[x][y],
                            min(dist[x][u] + w + dist[v][y],
                            dist[x][v] + w + dist[u][y]));
            }
        }
        cout<<show_sum(dist,n)<<" ";
    }
    return 0;
}