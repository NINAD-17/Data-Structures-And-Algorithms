#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

void prepareAdjList(vector<vector<int>> &edges, int e, unordered_map<int, set<int>> &adjList) {
    for(int i = 0; i < e; i++) {
        int startNode = edges[i][0];
        int endNode = edges[i][1];

        adjList[startNode].insert(endNode);
        adjList[endNode].insert(startNode);
    }
}

bool isCyclePresentBFS(int srcNode, unordered_map<int, bool> &isVisited, unordered_map<int, set<int>> &adjList) {
    unordered_map<int, int> parents;

    parents[srcNode] = -1; // Source node has no parent
    isVisited[srcNode] = true;

    queue<int> q;
    q.push(srcNode);

    while(!q.empty()) {
        int front = q.front();
        q.pop();

        for(int neighbor : adjList[front]) {
            if(isVisited[neighbor] == true && neighbor != parents[front])
                return true;
            else if(!isVisited[neighbor]) {
                q.push(neighbor);
                isVisited[neighbor] = true;
                parents[neighbor] = front;
            }
        }
    }

    return false;
}

string cycleDetection(vector<vector<int>> &edges, int v, int e) {
    unordered_map<int, set<int>> adjList;
    prepareAdjList(edges, e, adjList);

    unordered_map<int, bool> isVisited;

    for(int i = 0; i < v; i++) {
        if(!isVisited[i]) {
            bool ans = isCyclePresentBFS(i, isVisited, adjList);

            if(ans == true)
                return "Yes";
        }
    }

    return "No";
}

int main() {
    // ---------------------------------------------
    // Test Case 1: Graph WITH a cycle (0 - 1 - 2 - 0)
    // ---------------------------------------------
    int v1 = 4;
    int e1 = 4;
    vector<vector<int>> edgesWithCycle = {
        {0, 1},
        {1, 2},
        {2, 0},
        {2, 3}};

    cout << "Test Case 1 (Cycle Graph): "
         << cycleDetection(edgesWithCycle, v1, e1)
         << " (Expected: Yes)\n";

    // ---------------------------------------------
    // Test Case 2: Graph WITHOUT a cycle (Tree: 0 - 1, 1 - 2, 1 - 3)
    // ---------------------------------------------
    int v2 = 4;
    int e2 = 3;
    vector<vector<int>> edgesWithoutCycle = {
        {0, 1},
        {1, 2},
        {1, 3}};

    cout << "Test Case 2 (Acyclic Graph): "
         << cycleDetection(edgesWithoutCycle, v2, e2)
         << " (Expected: No)\n";

    return 0;
}