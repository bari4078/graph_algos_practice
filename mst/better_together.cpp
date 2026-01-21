#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    int M;
    cin >> N >> M;

    vector<ll> A(M), C(M);
    for (int i = 0; i < M; i++) cin >> A[i] >> C[i];

    // Step 1: Check gcd
    ll G = 0;
    for (int i = 0; i < M; i++) G = gcd(G, A[i]);
    G = gcd(G, N);

    if (G != 1) {
        cout << -1 << "\n";
        return 0;
    }

    // Step 2: Dijkstra on modulo N
    vector<ll> dist(N, INF);
    dist[0] = 0;

    using P = pair<ll, ll>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, 0}); // {cost, remainder}

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (dist[u] < cost) continue;

        for (int i = 0; i < M; i++) {
            ll v = (u + A[i]) % N;
            ll new_cost = cost + C[i];
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                pq.push({new_cost, v});
            }
        }
    }

    // Step 3: Minimum cost to connect all cities
    cout << dist[1] << "\n";

    return 0;
}
