#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int INF = 1e9;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
char dir[4] = {'D','U','R','L'};

int main(){
    int n,m;
    cin>>n>>m;
    
    vector< vector<char> > g(n,vector<char>(m));
    int sx,sy;
    queue< pair<int,int> > mon;
    vector< vector<int> > mon_time(n, vector<int>(m,INF));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>g[i][j];
            if(g[i][j] == 'A'){
                sx = i; sy = j;
            }
            else if(g[i][j] == 'M'){
                mon.push( {i,j} );
                mon_time[i][j] = 0;
            }
        }
    }

    while(!mon.empty()){
        auto [x,y] = mon.front(); mon.pop();

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || ny < 0 || nx >=n || ny >= m) continue;
            if(g[nx][ny] == '#') continue;
            
            if(mon_time[nx][ny] > mon_time[x][y] + 1){

                mon_time[nx][ny] = mon_time[x][y] + 1;
                mon.push( {nx,ny} );

            }
        }
    }

    vector< vector<int> > dist(n,vector<int>(m,INF));
    vector< vector<char> > path(n, vector<char>(m));
    queue< pair<int,int> > q;
    q.push({sx,sy});
    dist[sx][sy] = 0;

    if(sx == 0 || sy == 0 || sx == n-1 || sy == m-1){
        cout<<"YES"<<endl;
        cout<<0<<endl;
        return 0;
    }

    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        int curr_dist = dist[x][y];

        for(int i=0;i<4;i++){
            int nx = x + dx[i]; int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >=n || ny >= m) continue;
            if(g[nx][ny] == '#') continue;
            if(curr_dist + 1 >= mon_time[nx][ny]) continue;
            if(dist[nx][ny] != INF) continue;

            dist[nx][ny] = curr_dist + 1;
            path[nx][ny] = dir[i];

            q.push({nx,ny});

            if(nx == 0 || ny == 0 || nx == n-1 || ny == m-1){
                cout<<"YES\n";

                string p;
                int u = nx; int v = ny;
                while(1){
                    if(u == sx && v == sy) break;
                    p.push_back(path[u][v]);

                    if(path[u][v] == 'L') v++;
                    else if(path[u][v] == 'R') v--;
                    else if(path[u][v] == 'U') u++;
                    else if(path[u][v] == 'D') u--;
                }
                cout<<p.size()<<"\n";
                reverse(p.begin(),p.end());
                cout<<p;
                return 0;
            }
        }
    }
    cout<<"NO";
    return 0;
}