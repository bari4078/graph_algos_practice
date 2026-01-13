#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <map>
#include <string>
#include <climits>
#include <set>
#include <iomanip>

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main(){
    int a, b;
    int caseNo = 1;

    while (true) {
        vector<pair<int,int>> edges;

        while (cin >> a >> b) {
            if (a == 0 && b == 0) break;   
            edges.push_back({a, b});
        }

        if (edges.empty()) break;          

        vector< vector<ll> > dist(101, vector<ll> (101,INF));

        for(int i=1;i<=100;i++){
            dist[i][i] = 0;
        }
        set<int> nodes;

        for(auto &e: edges){
            int u = e.first;
            int v = e.second;
            nodes.insert(u);
            nodes.insert(v);
            dist[u][v] = 1;
        }

        for(int k:nodes){
            for(int i:nodes){
                for(int j:nodes){
                    if(dist[i][k] != INF && dist[k][j] != INF &&
                        dist[i][j] > dist[i][k] + dist[k][j]){
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                }
            }
        }

        ll sum = 0;
        ll count = 0;

        for(auto i:nodes){
            for(auto j:nodes){
                if(i != j){
                    sum += dist[i][j];
                    count++;
                }
            }
        }
        double average = (float) sum / count;
        cout<<fixed<<setprecision(3);
        cout<<"Case "<<caseNo<<": average length between pages = "
        <<average<<" clicks\n";

        caseNo++;
    }
}