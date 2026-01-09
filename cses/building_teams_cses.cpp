#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;


int main(){
    int n,m;
    cin>>n>>m;
    vector< vector<int> > g(n+1);
    vector<int> color(n+1,-1);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i=0; i<n+1;i++){
        if(color[i] == -1){
            queue<int> q;
            q.push(i);
            color[i] = 1;

            while(!q.empty()){
                int u = q.front(); q.pop();

                for(int v: g[u]){
                    if(color[v] == color[u]){
                        cout<<"IMPOSSIBLE";
                        return 0;
                    }
                    else if(color[v] == -1){
                        color[v] = (color[u] == 1 ? 2:1);
                        q.push(v);
                    }
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        cout<<color[i]<<" ";
    }
    return 0;
}