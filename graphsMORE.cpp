#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include <algorithm> // For generating permutations

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

    // Breadth-First Search (BFS)
    void BFS(int start) {
        vector<bool> visited(n_vert, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int neighbor : adjList[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS)
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(n_vert, false);
        DFSUtil(start, visited);
        cout << endl;
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

    // Dijkstra's Algorithm (for shortest path)
    vector<int> Dijkstra(int start) {
        vector<int> dist(n_vert, INT_MAX); // Distance vector initialized to "infinity"
        vector<bool> visited(n_vert, false);
        dist[start] = 0;

        for (int i = 0; i < n_vert; i++) {
            int u = -1;

            // Find the unvisited vertex with the smallest distance
            for (int j = 0; j < n_vert; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INT_MAX) break; // Remaining vertices are inaccessible

            visited[u] = true;
            for (int v : adjList[u]) {
                // For an undirected graph, adjust the condition to account for edge weights if present
                if (dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;  // This assumes unit edge weights; adjust for actual weights
                }
            }
        }

        return dist;
    }

    // Bellman-Ford Algorithm (for shortest path with negative weights)
    vector<int> BellmanFord(int start) {
        vector<int> dist(n_vert, INT_MAX);
        dist[start] = 0;

        for (int i = 0; i < n_vert - 1; i++) {
            for (int u = 0; u < n_vert; u++) {
                for (int v : adjList[u]) {
                    if (dist[u] != INT_MAX && dist[u] + 1 < dist[v]) {
                        dist[v] = dist[u] + 1;  // Adjust for edge weights
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < n_vert; u++) {
            for (int v : adjList[u]) {
                if (dist[u] != INT_MAX && dist[u] + 1 < dist[v]) {
                    cout << "Negative weight cycle detected!" << endl;
                    return {};
                }
            }
        }

        return dist;
    }

    // Traveling Salesman Problem (TSP) - Brute Force
    int TSP() {
        vector<int> vertices;
        for (int i = 0; i < n_vert; i++) {
            vertices.push_back(i);
        }

        int minPathCost = INT_MAX;
        do {
            int currentPathCost = 0;
            for (int i = 0; i < n_vert - 1; i++) {
                // Assuming edge weights are 1 between adjacent vertices, adjust as necessary
                currentPathCost += 1;
            }
            currentPathCost += 1; // Closing the cycle

            minPathCost = min(minPathCost, currentPathCost);
        } while (next_permutation(vertices.begin(), vertices.end()));

        return minPathCost;
    }
};

int main() {
    cout << "Graph using Adjacency List (Directed):\n";
    Graphs g(5, true);  // Create a directed graph with 5 vertices

    // Adding edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 1);  // Adding a cycle

    // Print the adjacency list
    g.printGraph();

    // BFS
    cout << "\nBFS starting from vertex 0: ";
    g.BFS(0);

    // DFS
    cout << "\nDFS starting from vertex 0: ";
    g.DFS(0);

    // Cycle Detection
    cout << "\nCycle Detection: ";
    cout << (g.hasCycle() ? "Cycle found" : "No cycle") << endl;

    // Dijkstra's Algorithm
    vector<int> dijkstraDistances = g.Dijkstra(0);
    cout << "\nDijkstra's shortest path distances from vertex 0:\n";
    for (int i = 0; i < dijkstraDistances.size(); i++) {
        cout << "Vertex " << i << ": " << (dijkstraDistances[i] == INT_MAX ? -1 : dijkstraDistances[i]) << endl;
    }

    // Bellman-Ford Algorithm
    vector<int> bellmanFordDistances = g.BellmanFord(0);
    cout << "\nBellman-Ford shortest path distances from vertex 0:\n";
    for (int i = 0; i < bellmanFordDistances.size(); i++) {
        cout << "Vertex " << i << ": " << (bellmanFordDistances[i] == INT_MAX ? -1 : bellmanFordDistances[i]) << endl;
    }

    // Traveling Salesman Problem (TSP)
    cout << "\nTraveling Salesman Problem (TSP) solution: ";
    cout << "Minimum path cost: " << g.TSP() << endl;

    return 0;
}
