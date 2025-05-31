#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;  // Adjacency list
int cutCount = 0;

int dfs(int node, int parent) {
    cout << "Visiting node " << node << " from parent " << parent << endl;
    int subtreeSize = 1;

    for (int neighbor : adj[node]) {
        if (neighbor != parent) {
            int childSize = dfs(neighbor, node);
            cout << "Returned from child " << neighbor << " to node " << node
                 << " with subtree size " << childSize << endl;

            if (childSize % 2 == 0) {
                cutCount++;
                cout << "CUT edge between " << node << " - " << neighbor << " ✅" << endl;
            } else {
                subtreeSize += childSize;
            }
        }
    }

    cout << "Subtree rooted at " << node << " has size " << subtreeSize << endl;
    return subtreeSize;
}


int evenForest(int t_nodes, int t_edges, vector<int> t_from, vector<int> t_to) {
    // Initialize adjacency list
    adj.assign(t_nodes + 1, vector<int>());

    // Build undirected tree
    for (int i = 0; i < t_edges; i++) {
        adj[t_from[i]].push_back(t_to[i]);
        adj[t_to[i]].push_back(t_from[i]);
    }

    dfs(1, 0);  // Start DFS from node 1, with parent 0

    return cutCount;
}



int main() {
    int nodes = 10, edges = 9;
    vector<int> t_from = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> t_to   = {1, 1, 3, 2, 1, 2, 6, 8, 8};

    cout << evenForest(nodes, edges, t_from, t_to) << endl;  // Output: 2
    return 0;
}
