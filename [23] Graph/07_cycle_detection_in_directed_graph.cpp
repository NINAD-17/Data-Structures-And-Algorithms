#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

// Cycle Detection In Directed Graph Using DFS

void prepareAdjList(vector<pair<int, int>> &edges, unordered_map<int, set<int>> &adjList) {
    for(const auto &edge : edges) {
        int startNode = edge.first;
        int endNode = edge.second;

        // Directed Graph: only startNode -> endNode
        adjList[startNode].insert(endNode);
    }
}

bool isCyclePresentDFS(int srcNode, unordered_map<int, bool> &isVisited, unordered_map<int, bool> &dfsVisited, unordered_map<int, set<int>> &adjList) {
    isVisited[srcNode] = true;
    dfsVisited[srcNode] = true;

    for(auto neighbor : adjList[srcNode]) {
        if(!isVisited[neighbor]) {
            bool cycleDetected = isCyclePresentDFS(neighbor, isVisited, dfsVisited, adjList);

            if(cycleDetected)
                return true;
        } else if(dfsVisited[neighbor]) {
            // Node is visited in the CURRENT recursion stack -> cycle detected
            return true;
        }
    }

    // Backtrack: remove from current recursion path
    dfsVisited[srcNode] = false;
    return false;
}

bool detectCycleInDirectedGraph(int v, vector<pair<int, int>> &edges) {
    unordered_map<int, set<int>> adjList;
    prepareAdjList(edges, adjList);

    unordered_map<int, bool> isVisited;
    unordered_map<int, bool> dfsVisited;

    // Call DFS for all components
    for(int node = 0; node < v; node++) {
        if(!isVisited[node]) {
            bool cycleDetected = isCyclePresentDFS(node, isVisited, dfsVisited, adjList);

            if(cycleDetected)
                return true;
        }
    }

    return false;
}

int main() {
    // -----------------------------------------------------------
    // Test Case 1: Directed graph WITH a cycle (0 -> 1 -> 2 -> 0)
    // -----------------------------------------------------------
    int v1 = 4;
    vector<pair<int, int>> edgesWithCycle = {
        {0, 1},
        {1, 2},
        {2, 0},
        {2, 3}};

    bool hasCycle1 = detectCycleInDirectedGraph(v1, edgesWithCycle);
    cout << "Test Case 1 (Cycle Graph): "
         << (hasCycle1 ? "Cycle Detected" : "No Cycle")
         << " (Expected: Cycle Detected)\n";

    // -----------------------------------------------------------
    // Test Case 2: Directed graph WITHOUT a cycle (DAG: 0 -> 1, 0 -> 2, 1 -> 2)
    // -----------------------------------------------------------
    int v2 = 3;
    vector<pair<int, int>> edgesWithoutCycle = {
        {0, 1},
        {0, 2},
        {1, 2}};

    bool hasCycle2 = detectCycleInDirectedGraph(v2, edgesWithoutCycle);
    cout << "Test Case 2 (DAG - No Cycle): "
         << (hasCycle2 ? "Cycle Detected" : "No Cycle")
         << " (Expected: No Cycle)\n";

    return 0;
}