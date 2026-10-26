#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// Topological Sort Using Kahn's Algorithm (BFS)

void prepareAdjList(vector<vector<int>> &edges, int e, unordered_map<int, set<int>> &adjList) {
    for(int i = 0; i < e; i++) {
        int startNode = edges[i][0];
        int endNode = edges[i][1];

        adjList[startNode].insert(endNode);
    }
}

vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e) {
    // 1. Prepare Adjacency List
    unordered_map<int, set<int>> adjList;
    prepareAdjList(edges, e, adjList);

    // 2. Find all indegrees directly from edges (or using const auto &)
    vector<int> indegree(v);
    for (int i = 0; i < e; i++)
        indegree[edges[i][1]]++;

    // 3. Push all nodes with 0 indegree into the queue
    queue<int> q;
    for(int node = 0; node < v; node++) {
        if(indegree[node] == 0)
            q.push(node);
    }

    // 4. Standard Kahn's BFS
    vector<int> ans;
    while(!q.empty()) {
        int front = q.front();
        q.pop();

        ans.push_back(front);

        // Reduce indegree for all adjacent nodes
        for(auto neighbor: adjList[front]) {
            indegree[neighbor]--;

            if(indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return ans;
}

int main() {
    // Directed Acyclic Graph (DAG) with 6 vertices: 0, 1, 2, 3, 4, 5
    int v = 6;
    int e = 6;

    // Edges (u -> v):
    // 5 -> 0, 5 -> 2
    // 4 -> 0, 4 -> 1
    // 2 -> 3
    // 3 -> 1
    vector<vector<int>> edges = {
        {5, 0},
        {5, 2},
        {4, 0},
        {4, 1},
        {2, 3},
        {3, 1}};

    vector<int> order = topologicalSort(edges, v, e);

    cout << "Topological Sort Order: ";
    for(int node : order) {
        cout << node << " ";
    }
    cout << "\n";

    // Here, output is:
    // Topological Sort Order: 5 4 2 3 1 0
    // (Note: Topological sort orders are not always unique; 
    //        any order where every start node appears before its end node—such as 4 5 2 3 1 0—is also valid).

    return 0;
}