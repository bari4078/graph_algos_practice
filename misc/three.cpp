#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

bool cycle = false;

void dfs(vector<vector<int>> &g, vector<int> &state, vector<int> &res, int u){
    state[u] = 1;
    for(int v : g[u]){
        if(state[v] == 1){
            cycle = true;
            return;
        }

        else if(state[v] == 0){
            dfs(g,state,res,v);
        }
    }
    res.push_back(u);
    state[u] = 2;
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> g(n+1);
    vector<int> state(n+1,0);
    vector<int> res;

    for(int i=0; i<m; i++){
        int u,v;
        cin>>u>>v;

        g[u].push_back(v);
    }

    for(int j = 1; j<=n; j++){
        if(state[j] == 0){
            dfs(g,state,res,j);
        }
    }

    if(cycle){
        cout<<"-1";
        return 0;
    }

    for(int i = res.size() -1; i >= 0; i--){
        cout<<res[i]<<" ";
    }

    return 0;
}