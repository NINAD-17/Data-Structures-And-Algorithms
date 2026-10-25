#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// For time complexity refer README.md
class Graph {
    public:
        unordered_map<int, vector<int>> adj; // Adjacency List

        void addEdge(int startNode, int endNode, bool isDirected) {
            // Note: `isDirected = false` means undirected graph and `true` means directed graph

            // Create an edge from start node to end node
            adj[startNode].push_back(endNode);

            if(!isDirected) {
                // Undirected Graph - means from both nodes connection is possible
                adj[endNode].push_back(startNode);
            }
        }

        void printAdjList() {
            for(const auto &pair: adj) { // Node to Node mapping
                int node = pair.first; // startNode
                const auto &neighbors = pair.second; // Neighbors or endNodes <vector>

                cout << node << ": ";
                for(int neighbor: neighbors)
                    cout << neighbor << " ";

                cout << endl;
            }
        }
};

int main() {
    int numOfNodes;
    cout << "Enter total number of nodes > ";
    cin >> numOfNodes;

    int numOfEdges;
    cout << "Enter total number of edges > ";
    cin >> numOfEdges;

    Graph g;

    for(int edge = 0; edge < numOfEdges; edge++) {
        int startNode, endNode;
        cin >> startNode;
        cin >> endNode;

        // Creating an undirected graph
        g.addEdge(startNode, endNode, false);
    }

    // Printing graph
    cout << endl << "Adjacency List: " << endl;
    g.printAdjList();

    return 0;
}

// Example Inputs:
// Enter total number of nodes > 5
// Enter total number of edges > 6
// 0 1
// 1 2
// 2 3
// 3 1
// 3 4 
// 0 4