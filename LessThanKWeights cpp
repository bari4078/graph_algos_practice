Can you give complete solution for this problem
Connectivity Under Edge Constraints
“Using only edges with weight ≤ X, is the graph connected?”
Often used inside:
binary search
sliding window

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        components = n;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[b] > sz[a]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        components--;
    }

    bool isConnected() {
        return components == 1;
    }
};

struct Edge {
    int u, v;
    long long w;
};

bool connectedWithLimit(int n, const vector<Edge>& edges, long long X) {
    DSU dsu(n);
    for (const auto &e : edges) {
        if (e.w <= X) {
            dsu.unite(e.u, e.v);
        }
    }
    return dsu.isConnected();
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    long long X;
    cin >> X;

    if (connectedWithLimit(n, edges, X))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
