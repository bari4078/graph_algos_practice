#include <bits/stdc++.h>
using namespace std;

using ll = long long;


struct Edge{
    int v;
    ll cap;
    ll flow;
    int rev;
};

vector< vector<Edge> > g;

void addEdge(int u,int v, int w){
    Edge forward = {v,w,0,(int)g[v].size()};
    Edge backward = {u,0,0,(int)g[u].size()};

    g[u].push_back(forward);
    g[v].push_back(backward);
}

bool bfs(int s,int t,vector<pair<int,int>> &parent){
    fill(parent.begin(), parent.end(), make_pair(-1, -1));

    queue<int> q;
    q.push(s);
    parent[s] = {s,-1};

    while(!q.empty()){
        int u = q.front();
        q.pop();
        int gSize = g[u].size();
        for(int i=0;i<gSize;i++){
            Edge &e = g[u][i];
            if( e.cap - e.flow > 0 && parent[ e.v ].first == -1){
                parent[e.v] = {u,i};
                if(e.v == t) return true;
                q.push(e.v);
            }
        }
    }
    return false;
}

ll edmonds_karp(int s,int t){
    ll maxFlow = 0;
    vector<pair<int,int>> parent(g.size());

    while(bfs(s,t,parent)){
        ll bottleneck = INT_MAX;

        for(int v = t; v != s;){
            auto augmentEdge = parent[v];

            auto u = augmentEdge.first;
            auto idx = augmentEdge.second;

            bottleneck = min(bottleneck, g[u][idx].cap - g[u][idx].flow);
            v = u;
        }

        for(int v = t; v != s;){
            auto augmentEdge = parent[v];

            auto u = augmentEdge.first;
            auto idx = augmentEdge.second;

            g[u][idx].flow += bottleneck;
            g[v][ g[u][idx].rev ].flow -= bottleneck;
            v = u;
        }

        maxFlow += bottleneck;
    }
    return maxFlow;
}

int main(){
    int n,m;
    cin>>n>>m;

    g.resize(n+1);

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }

    ll maxFlow = edmonds_karp(1,n);

    cout<<maxFlow;
    return 0;
}