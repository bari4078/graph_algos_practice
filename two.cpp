#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

void dfs(vector<vector<int>> &g, vector<vector<int>> &vis, int x, int y){
    vis[x][y] = 1;

    vector<int> dx = {1,-1,0,0};
    vector<int> dy = {0,0,1,-1};

    int n = g.size();
    int m = g[0].size();

    for(int k=0; k<4; k++){
        int nx = x + dx[k];
        int ny = y + dy[k];

        if(!(nx >= n || ny >= m) && g[nx][ny] == 0 && vis[nx][ny] == 0){
            dfs(g,vis,nx,ny);
        }
    }
}


int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> g(n, vector<int>(m));
    vector<vector<int>> vis(n,vector<int>(m));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>g[i][j];
            vis[i][j] = 0;
        }
    }

    int rooms = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j] && g[i][j] == 0){
                rooms++;
                dfs(g,vis,i,j);
            }
        }
    }

    cout<<"rooms: "<<rooms;
}