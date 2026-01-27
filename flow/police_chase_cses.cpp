#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v;
    int cap;
    int flow;
    int rev;
};


vector<vector<Edge>> g;


void addEdge(int u, int v, int c) {
    Edge forward = {v, c, 0, (int)g[v].size()};
    Edge backward = {u, 0, 0, (int)g[u].size()};
    
    g[u].push_back(forward);
    g[v].push_back(backward);
}


bool bfs(int s,int t, vector<pair<int,int>> &parent){
    fill(parent.begin(), parent.end(), make_pair(-1, -1));

    // for (int i = 0; i < parent.size(); i++) {
    //     parent[i].first = -1;
    //     parent[i].second = -1;
    // }

    queue<int> q;
    q.push(s);
    parent[s] = {s,-1};

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i=0;i<g[u].size();i++){
            Edge &e = g[u][i];

            if(parent[ e.v ].first == -1 && e.cap - e.flow > 0){
                parent[ e.v ] = {u,i};
                if(e.v == t) return true;
                q.push(e.v);
            }
        }
    }

    return false;
}

int edmondsKarp(int s,int t){
    int maxFlow = 0;
    vector< pair<int,int> > parent(g.size());

    while(bfs(s,t,parent)){
        int bottleneck = INT_MAX;

        for(int v = t; v != s; ){
            auto augmentEdge = parent[v];

            auto u = augmentEdge.first;
            auto idx = augmentEdge.second;

            bottleneck = min(bottleneck, g[u][idx].cap - g[u][idx].flow);
            v = u;
        }

        for(auto v = t; v != s; ){
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
    vector< pair<int,int> > inputEdges;

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        addEdge(u,v,1);
        addEdge(v,u,1);
        inputEdges.push_back({u,v});
    }

    vector<bool> visited(n+1);
    int maxFlow = edmondsKarp(1,n);

    queue<int> q;
    q.push(1);
    visited[1] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto &e: g[u]){
            if(!visited[e.v] && (e.cap - e.flow) > 0){
                visited[e.v] = true;
                q.push(e.v);
            }
        }
    }
    cout<<maxFlow<<"\n";
    for(auto &e:inputEdges){
        if( (!visited[e.first] && visited[e.second]) || 
            (visited[e.first] && !visited[e.second]))
            cout<<e.first<<" "<<e.second<<"\n";
    }
    return 0;
}