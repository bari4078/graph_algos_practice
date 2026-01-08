#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int INF = 1e8;

int main(){
    int n,k;
    cin>>n>>k;

    vector<pair<int,int>> knights;
    vector<vector<int>> board(n,vector<int>(n));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>board[i][j];
            if(board[i][j] == 1) knights.push_back({i,j});
        }
    }

    vector<int> dx = {1,1,2,2,-1,-1,-2,-2};
    vector<int> dy = {2,-2,1,-1,2,-2,1,-1};

    vector< vector<vector<int>> > dist(k, vector<vector<int>>(n,vector<int>(n,INF)));

    for(int t=0;t<k;t++){
        auto [sx,sy] = knights[t];

        queue<pair<int,int>> q;
        q.push({sx,sy});
        dist[t][sx][sy] = 0;
        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();

            for(int i = 0; i< 8;i++){
                int nx = x + dx[i];
                int ny = y + dy[i];

                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                else if(dist[t][nx][ny] != INF) continue;

                dist[t][nx][ny] = dist[t][x][y] + 1;
                q.push({nx,ny});
            }
        }
    }
    
    long long ans = LLONG_MAX;

    for(int i = 0; i<n;i++){
        for(int j=0;j<n;j++){
            long long sum = 0;
            bool reach = true;
            for(int t =0;t<k;t++){
                if(dist[t][i][j] == INF){
                    reach = false;
                }
                sum += dist[t][i][j];
            }
            if(reach) ans = min(ans,sum);
        }
    }

    cout<<"Moves: "<<ans;
}