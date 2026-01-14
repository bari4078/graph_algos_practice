#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<bool>> even(n + 1, vector<bool>(n + 1, false));
    vector<vector<bool>> odd(n + 1, vector<bool>(n + 1, false));

    // zero-edge path (i -> i) is even
    for (int i = 1; i <= n; i++) {
        even[i][i] = true;
    }

    // edges: one edge = odd
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        odd[u][v] = true;   // directed
    }

    // Floyd–Warshall parity
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // even paths
                if ((even[i][k] && even[k][j]) || (odd[i][k] && odd[k][j]))
                    even[i][j] = true;

                // odd paths
                if ((even[i][k] && odd[k][j]) || (odd[i][k] && even[k][j]))
                    odd[i][j] = true;
            }
        }
    }

    // output
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (even[i][j] && odd[i][j]) cout << "BOTH ";
            else if (even[i][j]) cout << "EVEN ";
            else if (odd[i][j]) cout << "ODD ";
            else cout << "NO_PATH ";
        }
        cout << "\n";
    }

    return 0;
}
