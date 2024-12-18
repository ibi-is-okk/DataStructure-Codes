#include <iostream>
#include <queue>
using namespace std;

// Node struct to represent adjacency list entries
struct Node {
    int vertex;
    int weight; // To store edge weight
    Node* next;

    Node(int v, int w) {
        vertex = v;
        weight = w;
        next = nullptr;
    }
};

class Graph {
    int totalVertices; // Total number of vertices
    bool isDirected; // Flag to determine if the graph is directed or undirected
    Node** adjList; // Array of pointers to adjacency lists

public:
    Graph(int v, bool directed = true) { // directed defaults to true (directed graph)
        totalVertices = v;
        isDirected = directed;
        adjList = new Node* [v];
        for (int i = 0; i < v; ++i) {
            adjList[i] = nullptr;
        }
    }

    void addEdge(int src, int dest, int weight = 1) {
        // Add edge from src to dest
        Node* newNode = new Node(dest, weight);
        newNode->next = adjList[src];
        adjList[src] = newNode;     // adjlist is the headpointer

        // If undirected graph, add edge from dest to src
        if (!isDirected) {
            newNode = new Node(src, weight);
            newNode->next = adjList[dest];
            adjList[dest] = newNode;
        }
    }

    void printAdj() {
        for (int i = 0; i < totalVertices; ++i) {
            cout << i << " -> ";
            Node* temp = adjList[i];
            while (temp) {
                cout << "(" << temp->vertex << ", " << temp->weight << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void BFS(int start) {
        bool* visited = new bool[totalVertices] {false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal starting from vertex " << start << ": ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            Node* temp = adjList[current];
            while (temp) {
                if (!visited[temp->vertex]) {
                    visited[temp->vertex] = true;
                    q.push(temp->vertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
        delete[] visited;
    }

    void DFS(int start) {
        bool* visited = new bool[totalVertices] {false};
        cout << "DFS Traversal starting from vertex " << start << ": ";
        DFSVisit(start, visited);
        cout << endl;
        delete[] visited;
    }

    void DFSVisit(int vertex, bool* visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        Node* temp = adjList[vertex];
        while (temp) {
            if (!visited[temp->vertex]) {
                DFSVisit(temp->vertex, visited);
            }
            temp = temp->next;
        }
    }

    ~Graph() {
        for (int i = 0; i < totalVertices; ++i) {
            Node* temp = adjList[i];
            while (temp) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] adjList;
    }
};

int main() {
    Graph g(7, false); // false means undirected graph

    g.addEdge(0, 1, 200);
    g.addEdge(0, 6, 160);
    g.addEdge(1, 0, 200);
    g.addEdge(1, 3, 780);
    g.addEdge(2, 1, 1300);
    g.addEdge(2, 4, 600);
    g.addEdge(4, 2, 600);
    g.addEdge(4, 6, 800);
    g.addEdge(6, 4, 800);
    g.addEdge(5, 3, 1000);
    g.addEdge(3, 5, 1000);
    g.addEdge(3, 4, 1400);

    g.printAdj();
    cout << endl;
    g.BFS(0);
    g.DFS(2);

    return 0;
}
