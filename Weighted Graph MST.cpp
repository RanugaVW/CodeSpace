#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
using namespace std;

class Graph{
    int V;
    vector<vector<pair<int,int>>> adjList; //For example, an edge 0 → 1 of weight 10
                                           //And an edge 0 → 2 of weight 20:
                                           //0: (1, w=10) (2, w=20)
                                           
public: 
    explicit Graph(int vertices) : V(vertices), adjList(vertices){}

    //weighted edge
    void addEdge(int u, int v, int w, bool directed = false) {
        // 1) validate
        if (u < 0 || u >= V || v < 0 || v >= V)
            throw out_of_range("Vertex out of range");
    
        // 2) add the “forward” edge u→v
        adjList[u].emplace_back(v, w);
    
        // 3) if undirected, add the “back” edge v→u
        if (!directed)
            adjList[v].emplace_back(u, w);
    }

    //Print the adjacancy list of each vertex
    void printGraph() const {
        for (int u = 0; u < V; ++u) {
            cout << u << ": ";
            for (auto [v, w] : adjList[u])
                cout << "(" << v << "," << w << ") ";
            cout << "\n";
        }
    }

    //Prim's Algorithm for MST
    void primMST(int start = 0) const{
        using T = tuple<int,int,int>;
        priority_queue<T, vector<T>, greater<T>> pq; //Ordered by the weight assending order
        vector<bool> inMST(V, false); //Tracks which vertices are already in the MST.
        vector<int> key(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);

        key[start] = 0;
        pq.emplace(0,start,-1);

        int totalWeight = 0;
        cout << "Edges in MST: \n";
        while(!pq.empty()){
            auto[w, u, p] = pq.top();
            pq.pop();
            
            if(inMST[u]){
                continue;
            }
            inMST[u] = true;
            parent[u] = p;
            totalWeight += w;
            if(p != -1){
                cout << " - " << "(w = " << w << " ) \n";
            }

            for(auto[v,wt] : adjList[u]){
                if(!inMST[v] && wt < key[v]){
                    key[v] = wt;
                    pq.emplace(wt, v, u);
                }
            }
        }
        cout << "Total MST weight = " << totalWeight << endl;
    }
};

int main(){
    Graph g(6); //no.of Vertices
    
    //addEdge(u, v, weight)
    g.addEdge(0,1,7, true);
    g.addEdge(0,3,9, true);
    g.addEdge(0,2,3, true);
    g.addEdge(1,4,1, true);
    g.addEdge(4,3,1, true);
    g.addEdge(3,4,2, true);
    g.addEdge(3,1,-4,true);
    g.addEdge(2,3,2, true);

    cout << "Weighted Graph \n";
    g.printGraph();
    cout << endl;

    g.primMST(0); // Start from vertex 0
    return 0;
}

