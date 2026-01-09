#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int INF = 1e8;

void bfs(vector< vector<int>> &g,
        vector< int > &dist,
        vector<int> &par,
        int s){
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : g[u]){
            if(dist[v] >= INF){
                dist[v] = dist[u]+1;
                par[v] = u;
                q.push(v);
            }
        }
    }
}
vector<int> path(vector<int> &par,int n){
    vector<int> res;
    int curr = n;
    while(par[curr] != -1){
        res.push_back(curr);
        curr = par[curr];
    }
    reverse(res.begin(),res.end());
    return res;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector< vector<int> > g(n+1);
    vector<int> dist(n+1,INF);
    vector<int> par(n+1,-1);
    
    dist[1] = 0;
    par[1] = 0;

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs(g,dist,par,1);
    
    if(dist[n] >= INF) cout<<"IMPOSSIBLE";
    else{
        cout<<++dist[n]<<endl;
        auto res = path(par,n);
        for(auto c: res){
            cout<<c<<" ";
        }        

    }
    return 0;
}