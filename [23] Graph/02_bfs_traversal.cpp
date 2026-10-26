#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

void prepareAdjList(unordered_map<int, set<int>> &adjList, vector<pair<int, int>> &edges) {
    for(int i = 0; i < edges.size(); i++) {
        int startNode = edges[i].first;
        int endNode = edges[i].second;

        // Undirected graph: add connection in both directions
        adjList[startNode].insert(endNode);
        adjList[endNode].insert(startNode);
    }
}

void bfsTraversal(unordered_map<int, set<int>> &adjList, unordered_map<int, bool> &visited, vector<int> &ans, int startNode) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();

        ans.push_back(frontNode);

        // Traverse all neighbors of frontNode in sorted order
        for(int neighbor: adjList[frontNode]) {
            if(!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

vector<int> bfs(int vertex, vector<pair<int, int>> &edges) {
    vector<int> ans;
    unordered_map<int, set<int>> adjList;
    unordered_map<int, bool> visited; // to keep track of visited nodes

    prepareAdjList(adjList, edges);

    // Traverse all components (in case of disconnected graph) of a graph
    // Note: Assuming all nodes are lie in the range of 0 to (vertices - 1)
    //       If startNodes have different values and not in the range of 0 to (vertices - 1) refer 03_bfs_traversal_2.cpp
    for(int node = 0; node < vertex; node++) {
        if(!visited[node])
            bfsTraversal(adjList, visited, ans, node);
    }

    return ans;
}

int main() {
    // 5 vertices: 0, 1, 2, 3, 4
    int vertex = 5;

    // Disconnected graph:
    // Component 1: 0 - 1, 0 - 2
    // Component 2: 3 - 4
    vector<pair<int, int>> edges = {
        {0, 1},
        {0, 2},
        {3, 4}
    };

    vector<int> traversalOrder = bfs(vertex, edges);

    cout << "BFS Traversal of the graph: ";
    for(int node : traversalOrder) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}