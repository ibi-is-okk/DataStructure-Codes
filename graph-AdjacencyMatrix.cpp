#include<iostream>
#include<vector>
#include<queue>
using namespace std;

template<typename T>
class graph {
    int** Matrix; // 2D matrix representing adj vertices
    T* v_list; // list of vertices
    int total; // total number of vertices in graph
    int index; // current index to help store data in v_list
    bool isDirected; // Flag to determine if graph is directed or undirected
public:
    graph(int v, bool directed = true) {  // directed defaults to true (directed graph)
        total = v;
        v_list = new T[total];
        Matrix = new int* [total];
        for (int i = 0; i < total; i++)
            Matrix[i] = new int[total];

        for (int i = 0; i < total; i++) {
            for (int j = 0; j < total; j++)  // initialize matrix
                Matrix[i][j] = 0;
        }

        index = 0;
        isDirected = directed;  // set graph type (directed or undirected)
    }

    void addVertex(T v_info) {          // matrix mai ni cus it only represents edges btw 2 vertex
        if (index < total) {
            v_list[index++] = v_info;
        }
    }

    void addEdge(T src, T dest, int w = 1) { // w = weight
        int r = getIndex(src);
        int c = getIndex(dest);
        if (r == -1 || c == -1)
            cout << "either src or dest does not exist\n";
        else {
            Matrix[r][c] = w;
            if (!isDirected) { // For undirected graph, add reverse edge
                Matrix[c][r] = w;
            }
        }
    }

    int getIndex(T info) {
        for (int i = 0; i < total; i++) {
            if (v_list[i] == info)
                return i;
        }
        return -1;
    }

    void printAdj() {
        for (int i = 0; i < total; i++) {
            for (int j = 0; j < total; j++) {
                if (Matrix[i][j] != 0) {
                    cout << v_list[i] << " and " << v_list[j] << " are adjacent\n";
                    cout << "dist between the vert is " << Matrix[i][j] << endl;
                }
            }
        }
    }

    void BFS(T start) {
        int startIdx = getIndex(start);
        if (startIdx == -1) {
            cout << "Start vertex not found in graph.\n";
            return;
        }

        vector<bool> visited(total, false);
        queue<int> q;
        visited[startIdx] = true;
        q.push(startIdx);

        cout << "BFS Traversal starting from vertex " << start << ": ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << v_list[current] << ",";
            for (int i = 0; i < total; i++) {       // to check whole row
                if (Matrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    void DFS(T start) {
        int startIdx = getIndex(start);
        if (startIdx == -1) {
            cout << "Start vertex not found in graph.\n";
            return;
        }
        vector<bool> visited(total, false);
        cout << "DFS Traversal starting from vertex " << start << ": ";
        DFSVisit(startIdx, visited);
        cout << endl;
    }

    void DFSVisit(int v, vector<bool>& visited) {       //stack ni use ker rhay cus recursion works like a stack
        visited[v] = true;
        cout << v_list[v] << ",";
        for (int i = 0; i < total; i++) {               // check the row finds first and with recursion starts going to its neighbours
            if (Matrix[v][i] != 0 && !visited[i]) {     
                DFSVisit(i, visited);
            }
        }
    }
};

int main() {
    graph<string> g1(7, false); // false means undirected graph
    g1.addVertex("Austin");
    g1.addVertex("Dallas");
    g1.addVertex("Washington");
    g1.addVertex("Denver");
    g1.addVertex("Atlanta");
    g1.addVertex("Chicago");
    g1.addVertex("Houston");

    g1.addEdge("Austin", "Dallas", 200);
    g1.addEdge("Austin", "Houston", 160);
    g1.addEdge("Dallas", "Austin", 200);
    g1.addEdge("Dallas", "Denver", 780);
    g1.addEdge("Washington", "Dallas", 1300);
    g1.addEdge("Washington", "Atlanta", 600);
    g1.addEdge("Atlanta", "Washington", 600);
    g1.addEdge("Atlanta", "Houston", 800);
    g1.addEdge("Houston", "Atlanta", 800);
    g1.addEdge("Chicago", "Denver", 1000);
    g1.addEdge("Denver", "Chicago", 1000);
    g1.addEdge("Denver", "Atlanta", 1400);

    g1.printAdj();
    cout << endl;
    g1.BFS("Austin");
    g1.DFS("Washington");

    return 0;
}
