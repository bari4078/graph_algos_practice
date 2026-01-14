#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    vector<vector<int>> nxt(n, vector<int>(n, -1));

    // init
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        nxt[i][i] = i;
    }

    // input edges
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        if (w < dist[u][v]) {
            dist[u][v] = w;
            nxt[u][v] = v;
        }
    }

    // Floyd–Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }

    // function to print path from u to v
    auto print_path = [&](int u, int v) {
        if (nxt[u][v] == -1) {
            cout << "No path\n";
            return;
        }
        vector<int> path;
        path.push_back(u);
        while (u != v) {
            u = nxt[u][v];
            path.push_back(u);
        }
        for (int x : path) cout << x << " ";
        cout << "\n";
    };

    // example usage
    int u, v;
    cin >> u >> v;

    if (dist[u][v] == INF) {
        cout << "No path\n";
    } else {
        cout << "Distance: " << dist[u][v] << "\n";
        cout << "Path: ";
        print_path(u, v);
    }

    return 0;
}
