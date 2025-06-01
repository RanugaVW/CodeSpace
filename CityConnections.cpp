Graph Traversing

Detects if infinite paths exist due to cycles reachable from 1 and can reach n.

If infinite, prints "INFINITE PATHS".

Otherwise, counts the total number of distinct paths modulo 10^9.

Uses BFS for reachability, DFS with cycle detection, and DP with memoization for path counting. 

Mini

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countPaths' function below.
 *
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;

int n, m;
vector<vector<int>> graph;
vector<int> state; // 0=unvisited,1=visiting,2=done
vector<bool> reachableFrom1, reachableToN;
bool hasCycle = false;

// DFS to detect cycles on relevant nodes
void dfsCycle(int u) {
    if (hasCycle) return;
    state[u] = 1; // visiting
    for (int v : graph[u]) {
        if (!reachableFrom1[v] || !reachableToN[v]) continue; // ignore irrelevant nodes
        if (state[v] == 0) {
            dfsCycle(v);
        } else if (state[v] == 1) {
            hasCycle = true;
            return;
        }
    }
    state[u] = 2; // done
}

// BFS to find reachable nodes from start
vector<bool> bfsReach(int start) {
    vector<bool> reachable(n + 1, false);
    queue<int> q;
    reachable[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }
    return reachable;
}

// BFS on reversed graph to find nodes that can reach n
vector<bool> bfsReachToN() {
    vector<vector<int>> revGraph(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            revGraph[v].push_back(u);
        }
    }
    vector<bool> reachable(n + 1, false);
    queue<int> q;
    reachable[n] = true;
    q.push(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : revGraph[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }
    return reachable;
}

// DP memoization for counting paths from node u to n
vector<long long> dp;
bool dpVisited;

long long countPathsFrom(int u) {
    if (u == n) return 1;
    if (dp[u] != -1) return dp[u];
    long long ways = 0;
    for (int v : graph[u]) {
        if (!reachableFrom1[v] || !reachableToN[v]) continue;
        ways += countPathsFrom(v);
        if (ways >= MOD) ways %= MOD;
    }
    return dp[u] = ways;
}

void countPaths(int nodes, vector<vector<int>> edges) {
    n = nodes;
    graph.assign(n + 1, vector<int>());

    for (auto &e : edges) {
        graph[e[0]].push_back(e[1]);
    }

    reachableFrom1 = bfsReach(1);
    reachableToN = bfsReachToN();

    if (!reachableFrom1[n]) {
        cout << 0 << "\n";
        return;
    }

    state.assign(n + 1, 0);
    dfsCycle(1);

    if (hasCycle) {
        cout << "INFINITE PATHS\n";
        return;
    }

    dp.assign(n + 1, -1);
    cout << countPathsFrom(1) % MOD << "\n";
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int nodes = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++) {
        edges[i].resize(2);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    countPaths(nodes, edges);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}