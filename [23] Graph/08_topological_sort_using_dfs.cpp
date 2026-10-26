#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// Topological Sort Using DFS

void prepareAdjList(vector<vector<int>> &edges, int e, unordered_map<int, set<int>> &adjList) {
    for(int i = 0; i < e; i++) {
        int startNode = edges[i][0];
        int endNode = edges[i][1];

        adjList[startNode].insert(endNode);
    }
}

void prepareSortedOrder(int srcNode, unordered_map<int, bool> &isVisited, stack<int> &st, unordered_map<int, set<int>> &adjList) {
    isVisited[srcNode] = true;

    for(int neighbor : adjList[srcNode]) {
        if(!isVisited[neighbor])
            prepareSortedOrder(neighbor, isVisited, st, adjList);
    }

    // Push to stack on return from recursion (post-order)
    st.push(srcNode);
}

vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e) {
    // Prepare Adjacency List
    unordered_map<int, set<int>> adjList;
    prepareAdjList(edges, e, adjList);

    unordered_map<int, bool> isVisited;
    stack<int> st;

    // Call DFS for all components
    for(int node = 0; node < v; node++) {
        if(!isVisited[node])
            prepareSortedOrder(node, isVisited, st, adjList);
    }

    vector<int> ans;
    while(!st.empty()) {
        ans.push_back(st.top());
        st.pop();
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