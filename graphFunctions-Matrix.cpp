#include <iostream>
#include <vector>

using namespace std;

class Graphs {
private:
    int** matrix;     // Adjacency matrix
    int n_vert;       // Number of vertices
    bool isDirected;  // Flag to indicate if the graph is directed

public:
    // Constructor to initialize the graph
    Graphs(int total, bool dir) : n_vert(total), isDirected(dir) {
        matrix = new int* [n_vert];
        for (int i = 0; i < n_vert; i++) {
            matrix[i] = new int[n_vert] {0}; // Initialize matrix with 0
        }
    }

    ~Graphs() {
        for (int i = 0; i < n_vert; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    //  between vertices x and y
    bool addEdge(int x, int y) {
        if (x >= n_vert || y >= n_vert || x < 0 || y < 0)
            return false;
        matrix[x][y] = 1;  // Add edge from x to y
        if (!isDirected)
            matrix[y][x] = 1;  // If undirected, add edge from y to x
        return true;
    }


    bool removeEdge(int x, int y) {
        if (x >= n_vert || y >= n_vert || x < 0 || y < 0)
            return false;
        matrix[x][y] = 0;
        if (!isDirected)
            matrix[y][x] = 0;  // If undirected, remove edge from y to x
        return true;
    }

    // Prints the adjacency matrix
    void printGraph() {
        for (int i = 0; i < n_vert; i++) {
            for (int j = 0; j < n_vert; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Transposes the graph
    void transpose() {
        int** transposedMatrix = new int* [n_vert];
        for (int i = 0; i < n_vert; i++) {
            transposedMatrix[i] = new int[n_vert];
            for (int j = 0; j < n_vert; j++) {
                transposedMatrix[i][j] = matrix[j][i];  // Swap rows and columns
            }
        }

        // Replace original matrix with transposed matrix
        for (int i = 0; i < n_vert; i++) {
            delete[] matrix[i];
            matrix[i] = transposedMatrix[i];
        }
        delete[] transposedMatrix;
    }

    bool detectCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack) { //a cycle is a LOOP so dosent matter konsay vertex se shuru horha going along its path
        visited[v] = true;                                                       // kahin bhi cycle bn sakti
        recStack[v] = true;

        // Traverse all adjacent vertices
        for (int i = 0; i < n_vert; i++) {
            if (matrix[v][i] != 0) {     // CHECKs that whole row (in directed out degree)                   
                if (!visited[i]) {      // if 0
                    if (detectCycleUtil(i, visited, recStack))
                        return true;                        // Cycle detected weird case idk
                }
                else if (recStack[i]) {                     //      BASE CASE  if its alrdy visited
                    return true;                            // Back edge detected
                }
            }
        }

        recStack[v] = false;         // clears recStack, to now go to some other disconnected graph
        return false;                // No cycle detected along this path
    }

    bool hasCycle() {
        vector<bool> visited(n_vert, false);  //Tracks whether a node has been visited at all during the traversal.
        vector<bool> recStack(n_vert, false); // Tracks whether a node is part of the current path being expored        JUST FOR DISCONNECTRED GRAPHS


        for (int i = 0; i < n_vert; i++) {          // so even disconneted graphs our considered                 ____________________     if there is no disconneced
            if (!visited[i]) { // so that it only goes in the loop if there is some disconnected graph                               |    graph it dosent even go in 
                if (detectCycleUtil(i, visited, recStack))   //   while this follows a single path starting from each vertex <-     the loop again
                    return true;
            }
        }
        return false;
    }


    bool DFSPathUtil(int src, int dest, vector<bool>& visited) {
        if (src == dest) return true;  // Base case: reached the destination

        visited[src] = true;
        for (int i = 0; i < n_vert; i++) {
            if (matrix[src][i] != 0 && !visited[i])
                return DFSPathUtil(i, dest, visited);
        }
        return false;
    }

    bool pathExists(int src, int dest) {        //DFS
        if (src >= n_vert || dest >= n_vert || src < 0 || dest < 0)
            return false;

        vector<bool> visited(n_vert, false);
        return DFSPathUtil(src, dest, visited);
    }


    bool isComplete() {
        for (int i = 0; i < n_vert; i++) {
            for (int j = 0; j < n_vert; j++) {
                // A complete graph has an edge between every pair of distinct vertices   EXCEPT MAIN DIAGNOL WOH IS FOR LOOPS
                if (i != j && matrix[i][j] == 0) {
                    return false;  // Missing edge
                }
            }
        }
        return true;
    }


    int getIndegree(int vertex) {           // VERTEX BECOMES THE COLL NUM
        if (vertex >= 0 && vertex < n_vert) {
            int indegree = 0;
            for (int i = 0; i < n_vert; i++) {
                if (matrix[i][vertex] != 0) {
                    indegree++;
                }
            }
            return indegree;
        }
        return -1; // Invalid vertex
    }


    int getOutdegree(int vertex) {           // VERTEX BECOMES THE ROW NUM
        if (vertex >= 0 && vertex < n_vert) {
            int outdegree = 0;
            for (int i = 0; i < n_vert; i++) {
                if (matrix[vertex][i] != 0) {
                    outdegree++;
                }
            }
            return outdegree;
        }
        return -1; // Invalid vertex
    }
};

int main() {
    cout << "Graph using Adjacency Matrix (Directed):\n";
    Graphs g1(5, true);  // Create a directed graph with 5 vertices

    // Adding edges
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 1);  // Adding a cycle

    // Print the adjacency matrix
    g1.printGraph();

    // Cycle Detection
    cout << "\nCycle Detection: ";
    cout << (g1.hasCycle() ? "Cycle found" : "No cycle") << endl;

    // Path Finding
    cout << "\nPath from 0 to 3: ";
    cout << (g1.pathExists(0, 3) ? "Path exists" : "No path") << endl;

    // Transpose the graph and print
    cout << "\nTransposed Graph:\n";
    g1.transpose();
    g1.printGraph();

    // Degree of vertex 1
    cout << "\nIndegree of vertex 1: " << g1.getIndegree(1) << endl;        //starts from 0
    cout << "Outdegree of vertex 1: " << g1.getOutdegree(1) << endl;

    // Check if the graph is complete
    cout << "\nIs the graph complete? " << (g1.isComplete() ? "Yes" : "No") << endl;

    return 0;
}
