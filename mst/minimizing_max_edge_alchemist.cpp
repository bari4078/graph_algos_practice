#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> rows(n);
    for(int i = 0; i < n; i++) cin >> rows[i];

    vector<int> minDist(n, INT_MAX); // distance to marked set
    vector<bool> marked(n, false);

    minDist[0] = 0; // start with row 0
    int answer = 0;

    for(int i = 0; i < n; i++) {
        // pick unmarked row with minimum distance
        int u = -1;
        for(int j = 0; j < n; j++) {
            if(!marked[j] && (u == -1 || minDist[j] < minDist[u]))
                u = j;
        }

        marked[u] = true;
        answer = max(answer, minDist[u]); // track largest cost

        // update minDist for remaining unmarked rows
        for(int v = 0; v < n; v++) {
            if(!marked[v]) {
                int distUV = 0;
                for(int k = 0; k < m; k++)
                    distUV = max(distUV, abs(rows[u][k] - rows[v][k]));
                minDist[v] = min(minDist[v], distUV);
            }
        }
    }

    cout << answer << "\n";
}
