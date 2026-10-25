#include <bits/stdc++.h>
using namespace std;

// REFER ONLY 01_graph_creation.cpp NOT THIS FILE.
// IT'S EASY TO UNDERSTAND.

// THIS CODE IS TAUGHT IN VIDEO: https://youtu.be/EaK6aslcC5g

class Graph {
    public:
        unordered_map<int, list<int>> adj; // Adjacency List

        void addEdge(int u, int v, bool direction) {
            // direction -> 0 = undirected
            // direction -> 1 = directed

            adj[u].push_back(v);
            
            if(direction == 0) {
                adj[v].push_back(u);
            }
        }

        void printAdjList() {
            for(auto i: adj) {
                cout << i.first << " ---> ";
                for(auto j: i.second) {
                    cout << j << " ";
                }
                cout << endl;
            }
        }
};

int main() {
    int edges, nodes;

    cout << "Enter the number of nodes: ";
    cin >> nodes;

    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph g;

    for(int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;

        // Creating an undirected graph
        g.addEdge(u, v, 0);
    }

    g.printAdjList();
}