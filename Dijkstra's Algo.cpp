#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // pair<distance, node>

void dijkstra(int V, vector<vector<pii>>& adj, int start) {
    vector<int> dist(V, INT_MAX);
    dist[start] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue; // Ignore outdated entry

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest distances
    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << ": Unreachable\n";
        else
            cout << "Node " << i << ": " << dist[i] << "\n";
    }
}

int main() {
    int V = 6; // Number of vertices (0 to 5)
    vector<vector<pii>> adj(V);

    // Example graph
    // Edge: u -> v (weight)
    adj[0].push_back({1, 4});
    adj[0].push_back({2, 2});
    adj[1].push_back({2, 5});
    adj[1].push_back({3, 10});
    adj[2].push_back({4, 3});
    adj[4].push_back({3, 4});
    adj[3].push_back({5, 11});

    int start = 0;
    dijkstra(V, adj, start);

    return 0;
}
