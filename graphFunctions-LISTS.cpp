#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graphs {
private:
    vector<list<int>> adjList;  // Adjacency list (each vertex has a list of adjacent vertices)
    int n_vert;                 // Number of vertices
    bool isDirected;           // Flag to indicate if the graph is directed

public:
    // Constructor to initialize the graph
    Graphs(int total, bool dir) : n_vert(total), isDirected(dir) {
        adjList.resize(n_vert);  // Resize the adjacency list to hold n_vert lists
    }

    // Adds an edge between vertices x and y
    bool addEdge(int x, int y) {
        if (x >= n_vert || y >= n_vert || x < 0 || y < 0)
            return false;

        adjList[x].push_back(y);  // Add edge from x to y
        if (!isDirected)
            adjList[y].push_back(x);  // If undirected, add edge from y to x
        return true;
    }

    // Removes an edge between vertices x and y
    bool removeEdge(int x, int y) {
        if (x >= n_vert || y >= n_vert || x < 0 || y < 0)
            return false;

        adjList[x].remove(y);  // Remove edge from x to y
        if (!isDirected)
            adjList[y].remove(x);  // If undirected, remove edge from y to x
        return true;
    }

    // Prints the adjacency list
    void printGraph() {
        for (int i = 0; i < n_vert; i++) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Utility function for cycle detection using DFS
    bool detectCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (int i : adjList[v]) {
                if (!visited[i] && detectCycleUtil(i, visited, recStack))
                    return true;
                else if (recStack[i])
                    return true;
            }
        }
        recStack[v] = false;  // Remove vertex from recursion stack
        return false;
    }

    // DFS to detect cycle
    bool hasCycle() {
        vector<bool> visited(n_vert, false);
        vector<bool> recStack(n_vert, false);

        for (int i = 0; i < n_vert; i++) {
            if (detectCycleUtil(i, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    // DFS to check if a path exists between src and dest
    bool DFSPathUtil(int src, int dest, vector<bool>& visited) {
        if (src == dest) return true;  // Base case: reached the destination

        visited[src] = true;
        for (int i : adjList[src]) {  // Explore neighbors
            if (!visited[i])
                if (DFSPathUtil(i, dest, visited)) return true;
        }
        return false;
    }

    // Check if there is a path from src to dest
    bool pathExists(int src, int dest) {
        if (src >= n_vert || dest >= n_vert || src < 0 || dest < 0)
            return false;

        vector<bool> visited(n_vert, false);
        return DFSPathUtil(src, dest, visited);
    }

    // Check if the graph is complete
    bool isComplete() {
        for (int i = 0; i < n_vert; i++) {
            if (adjList[i].size() != n_vert - 1) {
                return false;  // A complete graph must have n-1 edges from each vertex
            }
        }
        return true;
    }

    // Get the indegree of a vertex
    int getIndegree(int vertex) {
        if (vertex < 0 || vertex >= n_vert)
            return -1;

        int indegree = 0;
        for (int i = 0; i < n_vert; i++) {
            if (find(adjList[i].begin(), adjList[i].end(), vertex) != adjList[i].end()) {
                indegree++;  // Count the edges pointing to 'vertex'
            }
        }
        return indegree;
    }

    // Get the outdegree of a vertex
    int getOutdegree(int vertex) {
        if (vertex < 0 || vertex >= n_vert)
            return -1;

        return adjList[vertex].size();  // The size of the list for vertex gives the outdegree
    }
};

int main() {
    cout << "Graph using Adjacency List (Directed):\n";
    Graphs g1(5, true);  // Create a directed graph with 5 vertices

    // Adding edges
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 1);  // Adding a cycle

    // Print the adjacency list
    g1.printGraph();

    // Cycle Detection
    cout << "\nCycle Detection: ";
    cout << (g1.hasCycle() ? "Cycle found" : "No cycle") << endl;

    // Path Finding
    cout << "\nPath from 0 to 3: ";
    cout << (g1.pathExists(0, 3) ? "Path exists" : "No path") << endl;

    // Degree of vertex 1
    cout << "\nIndegree of vertex 1: " << g1.getIndegree(1) << endl;
    cout << "Outdegree of vertex 1: " << g1.getOutdegree(1) << endl;

    // Check if the graph is complete
    cout << "\nIs the graph complete? " << (g1.isComplete() ? "Yes" : "No") << endl;

    return 0;
}
