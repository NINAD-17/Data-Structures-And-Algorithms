#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
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
        for(int neighbor : adjList[frontNode]) {
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

    // Collect all unique nodes present as keys in adjList
    vector<int> allNodes;
    for(const auto &pair : adjList)
        allNodes.push_back(pair.first);
    
    sort(allNodes.begin(), allNodes.end()); // guarantees smallest node first

    // Iterate through all nodes (regardless of their numerical values)
    for(int node : allNodes) {
        if(!visited[node]) {
            bfsTraversal(adjList, visited, ans, node);
        }
    }

    return ans;
}

int main() {
    // Arbitrary non-0-indexed node labels: 50, 60, 70, 80, 90
    // Disconnected graph:
    // Component 1: 50 - 60, 50 - 70
    // Component 2: 80 - 90
    int nodes = 5;

    vector<pair<int, int>> edges = {
        {50, 60},
        {50, 70},
        {80, 90}
    };

    vector<int> traversalOrder = bfs(nodes, edges);

    cout << "BFS Traversal of graph with arbitrary nodes: ";
    for (int node : traversalOrder) {
        cout << node << " ";
    }
    cout << "\n";

    return 0;
}