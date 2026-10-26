#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// Cycle Detection Using Kahn's Algorithm (BFS)

void prepareAdjList(vector<vector<int>> &edges, int e, unordered_map<int, set<int>> &adjList) {
    for(int i = 0; i < e; i++) {
        int startNode = edges[i][0];
        int endNode = edges[i][1];

        adjList[startNode].insert(endNode);
    }
}

bool isCyclePresentKahn(vector<vector<int>> &edges, int v, int e) {
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

    int count = 0;

    // 4. Standard Kahn's BFS
    while(!q.empty()) {
        int front = q.front();
        q.pop();

        count++;

        // Reduce indegree for all adjacent nodes
        for(auto neighbor: adjList[front]) {
            indegree[neighbor]--;

            if(indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    // If count == v, all nodes were processed in valid topological order -> No cycle
    // If count < v, some nodes remained in a cycle with in-degree > 0 -> Cycle present
    return (count != v);
}

int main() {
    // -------------------------------------------------------------
    // Test Case 1: Directed graph WITH a cycle
    // Cycle: 1 -> 2 -> 3 -> 1, and 0 -> 1
    // -------------------------------------------------------------
    int v1 = 4;
    int e1 = 4;
    vector<vector<int>> edgesWithCycle = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 1}
    };

    bool hasCycle1 = isCyclePresentKahn(edgesWithCycle, v1, e1);
    cout << "Test Case 1 (Graph with Cycle): " 
         << (hasCycle1 ? "Cycle Detected (true)" : "No Cycle (false)") 
         << " | Expected: Cycle Detected (true)\n";

    // -------------------------------------------------------------
    // Test Case 2: Directed Acyclic Graph (DAG) - NO cycle
    // Edges: 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3
    // -------------------------------------------------------------
    int v2 = 4;
    int e2 = 4;
    vector<vector<int>> edgesWithoutCycle = {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 3}
    };

    bool hasCycle2 = isCyclePresentKahn(edgesWithoutCycle, v2, e2);
    cout << "Test Case 2 (DAG without Cycle): " 
         << (hasCycle2 ? "Cycle Detected (true)" : "No Cycle (false)") 
         << " | Expected: No Cycle (false)\n";

    return 0;
}