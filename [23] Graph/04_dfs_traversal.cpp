#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

void prepareAdjList(vector<vector<int>> &edges, unordered_map<int, set<int>> &adjList) {
    for(const auto &edge : edges) {
        int startNode = edge[0];
        int endNode = edge[1];

        adjList[startNode].insert(endNode);
        adjList[endNode].insert(startNode);
    }
}

// Recursive DFS function to explore an entire connected component
void dfsTraversal(int currentNode, unordered_map<int, bool> &visited, unordered_map<int, set<int>> &adjList, vector<int> &component) {
    component.push_back(currentNode);
    visited[currentNode] = true;

    // Recursively visit all unvisited neighbors
    for(auto neighbor : adjList[currentNode]) {
        if(!visited[neighbor])
            dfsTraversal(neighbor, visited, adjList, component);
    }
}

vector<vector<int>> dfs(int v, int e, vector<vector<int>> &edges) {
    // Prepare Adjacency List
    unordered_map<int, set<int>> adjList;
    prepareAdjList(edges, adjList);

    unordered_map<int, bool> visited;
    vector<vector<int>> ans;

    // Check every node from 0 to v - 1 to handle disconnected components
    for(int node = 0; node < v; node++) {
        if(!visited[node]) {
            vector<int> component;
            dfsTraversal(node, visited, adjList, component);
            ans.push_back(component);
        }
    }

    return ans;
}

int main() {
    int v = 5; // Nodes: 0, 1, 2, 3, 4
    int e = 3;

    // Disconnected graph:
    // Component 1: 0 - 1, 0 - 2
    // Component 2: 3 - 4
    vector<vector<int>> edges = {
        {0, 1},
        {0, 2},
        {3, 4}};

    vector<vector<int>> components = dfs(v, e, edges);

    cout << "Total Components: " << components.size() << "\n";
    for(int i = 0; i < components.size(); i++) {
        cout << "Component " << i + 1 << ": ";
        for(int node : components[i]) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}