#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

void bfs(vector< vector<char> > &g,
        vector< vector<bool> > &vis,
        int x, int y){

            queue<pair <int,int> > q;
            q.push({x,y});
            int dx[4] = {1,-1,0,0};
            int dy[4] = {0,0,1,-1};

            vis[x][y] = true;

            while(!q.empty()){
                auto [ux,uy] = q.front(); q.pop();
                
                for(int i=0;i<4;i++){
                    int nx = ux + dx[i];
                    int ny = uy + dy[i];

                    if(nx < 0 || ny < 0 || nx >= g.size() || ny >= g[0].size()
                        || g[nx][ny] == '#' || vis[nx][ny]) continue;

                    vis[nx][ny] = true;
                    q.push({nx,ny});
                }
            }
        }

int main(){
    int n,m;
    cin>>n>>m;

    vector< vector<char> > g(n,vector<char>(m));
    vector< vector<bool> > vis(n,vector<bool>(m,false));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>g[i][j];
        }
    }

    int room_count = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j] && g[i][j] == '.'){
                room_count++;
                bfs(g,vis,i,j);
            }
        }
    }

    cout<<room_count;

    return 0;
}