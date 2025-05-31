#include <iostream>
#include <vector>
#include <limits>

#define INF numeric_limits<int>::max()

using namespace std;

// Bellman-Ford algorithm for single source shortest path
vector<int> bellmanFord(const vector<vector<pair<int, int>>>& graph, int V, int src) {
    vector<int> dist(V, INF); // Initialize distances as infinite
    dist[src] = 0; // Distance of source vertex from itself is always 0

    // Relax all edges |V| - 1 times
    for (int i = 0; i < V - 1; ++i) {
        // Loop through all edges
        for (int u = 0; u < V; ++u) {
            // Explore neighbors of u
            for (const auto& edge : graph[u]) {
                int v = edge.first;  // Neighbor vertex
                int weight = edge.second;  // Edge weight

                // Relax the edge if a shorter path is found
                if (dist[u] != INF && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Debug: Print the dist array at each iteration
        cout << "Iteration " << i + 1 << ": ";
        for (int i = 0; i < V; ++i) {
            if (dist[i] == INF)
                cout << "INF ";
            else
                cout << dist[i] << " ";
        }
        cout << endl;
    }

    // Check for negative weight cycles
    for (int u = 0; u < V; ++u) {
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                cout << "Graph contains a negative weight cycle" << endl;
                return {}; // Return an empty vector to indicate a negative cycle
            }
        }
    }

    return dist;
}

// Function to print shortest distances from source node to all other nodes
void printShortestDistances(const vector<int>& dist) {
    int V = dist.size();
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            cout << "Node " << i << ": unreachable\n";
        } else {
            cout << "Node " << i << ": " << dist[i] << endl;
        }
    }
}

int main() {
    // Define the graph using adjacency list
    // Each pair (v, w) means an edge from node u to node v with weight w
    vector<vector<pair<int, int>>> graph(7); // Graph with 7 vertices

    // Add edges to the graph (u → v with weight w)
    graph[0].emplace_back(1, 7);    // A -> B (weight 7)
    graph[0].emplace_back(2, 5);    // A -> C (weight 5)
    graph[0].emplace_back(3, 5);    // A -> D (weight 5)
    graph[1].emplace_back(4, -1);    // B -> E (weight -1)
    graph[2].emplace_back(4, 1);    // E -> D (weight 1)
    graph[2].emplace_back(1, -2);    // D -> E (weight 2)
    graph[3].emplace_back(2, -2);   // D -> B (weight -4)
    graph[3].emplace_back(5, -1);    // C -> D (weight 2)
    graph[4].emplace_back(6, 3);
    graph[5].emplace_back(6, 3);

    int src;
    cout << "Enter source node: ";
    cin >> src;

    // Apply Bellman-Ford algorithm
    vector<int> dist = bellmanFord(graph, 7, src);
    if (!dist.empty()) {
        printShortestDistances(dist);
    }

    return 0;
}
