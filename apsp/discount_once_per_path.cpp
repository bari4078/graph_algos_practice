#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX/2;

int main(){
int n; // number of nodes
vector<vector<ll>> w(n, vector<ll>(n, INF)); // original edges

vector<vector<ll>> distNo(n, vector<ll>(n, INF)); // discount not used
vector<vector<ll>> distYes(n, vector<ll>(n, INF)); // discount used

// initialize
for(int i = 0; i < n; i++) {
    distNo[i][i] = distYes[i][i] = 0;
}

for(int u = 0; u < n; u++) {
    for(int v = 0; v < n; v++) {
        if(w[u][v] < INF) {
            distNo[u][v] = w[u][v]; // take edge without discount
            distYes[u][v] = max(w[u][v]-1, 0ll); // take edge with discount
        }
    }
}

// Floyd-Warshall with 2 states
for(int k = 0; k < n; k++) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // if discount not used yet
            distNo[i][j] = min(distNo[i][j], distNo[i][k] + distNo[k][j]);
            
            // if discount already used
            distYes[i][j] = min({
                distYes[i][j], 
                distYes[i][k] + distYes[k][j], // already used
                distNo[i][k] + distYes[k][j]  // use discount on some edge in the middle
            });
        }
    }
}
}