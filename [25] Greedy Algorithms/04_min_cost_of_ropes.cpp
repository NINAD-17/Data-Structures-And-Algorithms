#include <bits/stdc++.h>
using namespace std;

// Minimum cost of ropes

int minCost(vector<int> &ropeConnectionCosts) {
    int n = ropeConnectionCosts.size();

    priority_queue<int, vector<int>, greater<int>> minHeap;
    int cost = 0;

    for(int i = 0; i < n; i++)
        minHeap.push(ropeConnectionCosts[i]);

    while(minHeap.size() > 1) {
        int first = minHeap.top();
        minHeap.pop();

        int second = minHeap.top();
        minHeap.pop();

        int mergedLength = first + second;
        cost += mergedLength;

        minHeap.push(mergedLength);
    }

    return cost;
}

int main() {
    vector<int> ropeConnectionCosts = {4, 3, 2, 6};

    cout << "Cost of min ropes to connect is " << minCost(ropeConnectionCosts) << endl;

    return 0;
}