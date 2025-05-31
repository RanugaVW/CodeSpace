#include <vector>
#include <stdexcept>
#include <iostream>
#include <queue>
using namespace std;

class Graph{
    int V; //NNo.of Vertices
    vector<vector<int>> adjList; //Adjacency Lists

    // Utility for recursive DFS
    void DFSUtil(int u, vector<bool>& visited) const{
        visited[u] = true;
        cout << u << " ";
        for(int v : adjList[u]){
            if(!visited[v]){ //if not visited
                DFSUtil(v, visited);
            }
        }
    }

public:
    //Construct a grpah with V vertices(0..V-1)
    explicit Graph(int vertices) : V(vertices), adjList(vertices){}

    // Add an edge u–v. If directed==false, also adds v–u.
    void addEdge(int u, int v, bool directed = false){
        if(u < 0 || u>= V || v < 0 || v >= V){
            throw out_of_range("Vertex out of Range");
        }
        adjList[u].push_back(v);
        if(!directed){ //if not directed
            adjList[v].push_back(u);
        }
    }

    //Return the neightbours of vertex u
    const vector<int>& getNeighbours(int u) const{
        if(u < 0 || u >= V){
            throw out_of_range("Vertex out of Range");
        }
        return adjList[u];
    }

    //Print the adjacancy list of each vertex
    void printGraph() const{
        for(int u = 0; u < V; u++){
            cout << u << " Vertex: ";
            for(int v : adjList[u]){
                cout << v <<  " ";
            }
            cout << endl;
        }

    }

    // Depth-First Search from start vertex
    void DFS(int start) const{
        if (start < 0 || start >= V){
            throw out_of_range("Star vertex out of range");
        }
        vector<bool> visited(V, false); //{false, false, false,...}
        cout << "DFS starting at " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    //Breadth-First Search from start vertex
    void BFS(int start) const{
        if(start < 0  || start >= V){
            throw out_of_range("Start vertex out of range");
        }
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);
        cout << "BFS is startting at " << start << ": ";

        while(!q.empty()){ //not empty
            int u = q.front(); //front in the queue
            q.pop();
            cout << u << " ";
            
            for(int v : adjList[u]){
                if(!visited[v]){ //if not visited
                    visited[v] = true;
                    q.push(v); //Push every neighbour to the queue 
                }
            }
        }
        cout << endl;
    }
};

int main(){
    Graph g(5); //Creating a grpah with 5 vertices

    //Add some undirected edges
    g.addEdge(0,1);
    g.addEdge(0,4);
    g.addEdge(1,3);
    g.addEdge(1,2);
    g.addEdge(3,4);

    //Print the adjacancy List
    cout << "Graph Adjacancy Lists: \n";
    g.printGraph();

    cout << "Neighbours of vertex 1: \n";
    for(int v : g.getNeighbours(1)){
        cout << v << " ";
    }
    cout << "\n\n";

    //Perform DFS
    g.DFS(1);

    //Perform BFS
    g.BFS(1);

    return 0;
}