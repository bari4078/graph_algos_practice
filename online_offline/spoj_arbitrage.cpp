#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <climits>
#include <cmath>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main(){
    ll n;
    cin>>n;
    int count = 1;
    while(n!=0){

        unordered_map<string,int> g;
    vector< vector<double> > dist(n,vector<double>(n,INF));

    for(int i = 0; i < n; i++){
        string name;
        cin>>name;
        g[name] = i;

        dist[i][i] = 0;
    }

    ll m;
    cin>>m;

    for(ll i = 0;i<m;i++){
        string name1,name2;
        double rate;
        cin>>name1>>rate>>name2;

        ll u = g[name1];
        ll v = g[name2];

        dist[u][v] = min(dist[u][v],-(log10(rate)));
    }

    for(ll k=0;k<n;k++){
        for(int j=0;j<n;j++){
            for(int i=0;i<n;i++){
                if(dist[i][k] != INF && dist[k][j] != INF 
                    && dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    bool flag = false;
    for(ll i=0;i<n;i++){
        if(dist[i][i] < 0){
            flag = true;
            break;
        }
    }
    
    if(flag) cout<<"Case "<<count<<": Yes\n";
    else cout<<"Case "<<count<<": No\n";
    count++;
    cin>>n;
}
    
}