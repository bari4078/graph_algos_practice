#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

int n,m;

bool bfs(vector< vector<char> > &g,
        vector< vector<char> > &vis,
        int x, int y){

    queue<pair<int,int>> q;
    q.push({x,y});

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};
    
    vis[x][y] = 'S';

    while(!q.empty()){
        auto [ux,uy] = q.front(); q.pop();
        
        for(int i=0;i<4;i++){
            int nx = ux + dx[i];
            int ny = uy + dy[i];

            if(nx < 0 || ny < 0 || nx >= n || ny >= m 
                || vis[nx][ny] != '0'
                || g[nx][ny] == '#') continue;

            if(dx[i] == 1) vis[nx][ny] = 'D';
            if(dx[i] == -1) vis[nx][ny] = 'U';
            if(dy[i] == 1) vis[nx][ny] = 'R';
            if(dy[i] == -1) vis[nx][ny] = 'L';


            if(g[nx][ny] == 'B') return true;
            q.push({nx,ny});
        }
    }
    return false;
}

pair<string,int> path(vector< vector<char> > &vis, int x, int y){
    string res = "";
    int count = 0;
    int cx = x, cy = y;
    while(1){
        if(vis[cx][cy] == 'S') break;

        res.push_back(vis[cx][cy]);
        count++;

        if(vis[cx][cy] == 'L') cy++;   
        else if(vis[cx][cy] == 'R') cy--;  
        else if(vis[cx][cy] == 'U') cx++;  
        else if(vis[cx][cy] == 'D') cx--;
    }
    reverse(res.begin(), res.end());
    return {res,count};
}

int main(){
    cin>>n>>m;
    int sx,sy;
    int tx,ty;
    vector< vector<char> > g(n,vector<char>(m));
    vector< vector<char> > vis(n,vector<char>(m,'0'));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>g[i][j];
            if(g[i][j] == 'A'){
                sx = i; sy = j;
            }
            else if(g[i][j] == 'B'){
                tx = i; ty = j;
            }
        }
    }

    if(bfs(g,vis,sx,sy)){
        cout<<"YES"<<endl;
        auto [res,count] = path(vis,tx,ty);
        cout<<count<<endl;
        cout<<res<<endl;
    }
    else cout<<"NO"<<endl;
    return 0;
}