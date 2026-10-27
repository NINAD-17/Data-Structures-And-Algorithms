#include <bits/stdc++.h>
using namespace std;

// Knapsack Problem
// Theif is robbing a store and carries maximal weight of W into his knapsack.
// There're N items and each item has weight of wi and value of vi
// Rob maximum value but it shouldn't exceed W weight

int solveUsingTabulationSpaceOptimized(vector<int> &weight, vector<int> &value, int n, int capacity) {
    vector<int> prev(capacity + 1, 0);
    vector<int> curr(capacity + 1, 0);

    for(int w = weight[0]; w <= capacity; w++) {
        if(weight[0] <= capacity)
            prev[w] = value[0];
        else
            prev[w] = 0;
    }

    for(int index = 1; index < n; index++) {
        for(int w = 0; w <= capacity; w++) {
            int include = 0;
            if(weight[index] <= w) {
                include = value[index] + prev[capacity - weight[index]];
            }

            int exclude = 0 + prev[w];

            curr[w] = max(include, exclude);
        }

        prev = curr;
    }
    
    return prev[capacity];
}

int solveUsingTabulation(vector<int> &weight, vector<int> &value, int n, int capacity) {
    vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

    for(int w = weight[0]; w <= capacity; w++) {
        if(weight[0] <= capacity)
            dp[0][w] = value[0];
        else
            dp[0][w] = 0;
    }

    for(int index = 1; index < n; index++) {
        for(int w = 0; w <= capacity; w++) {
            int include = 0;
            if(weight[index] <= w) {
                include = value[index] + dp[index - 1][capacity - weight[index]];
            }

            int exclude = 0 + dp[index - 1][w];

            dp[index][w] = max(include, exclude);
        }
    }
    
    return dp[n - 1][capacity];
}

int solveUsingMemoization(vector<int> &weight, vector<int> &value, int index, int capacity, vector<vector<int>> &dp) {
    if(index == 0) {
        if(weight[0] <= capacity)
            return value[0];
        else
            return 0;
    }

    if(dp[index][capacity] != -1) {
        return dp[index][capacity];
    }

    int include = 0;
    if(weight[index] <= capacity) {
        include = value[index] + solveUsingMemoization(weight, value, index - 1, capacity - weight[index], dp);
    }

    int exclude = 0 + solveUsingMemoization(weight, value, index - 1, capacity, dp);

    dp[index][capacity] = max(include, exclude);
    return dp[index][capacity];
}

int solve(vector<int> &weight, vector<int> &value, int index, int capacity) {
    // Base Case: If only one item to steal, then just compare its weight with the knapsack capacity.
    if(index == 0) {
        if(weight[0] <= capacity)
            return value[0];
        else
            return 0;
    }

    int include = 0;
    if(weight[index] <= capacity) {
        include = value[index] + solve(weight, value, index - 1, capacity - weight[index]);
    }

    int exclude = 0 + solve(weight, value, index - 1, capacity);

    int ans = max(include, exclude);
    return ans;
}

int knapsack(vector<int> &weight, vector<int> &value, int n, int maxWeight) {
    cout << solve(weight, value, n - 1, maxWeight) << endl; // index is the last element

    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
    cout << solveUsingMemoization(weight, value, n - 1, maxWeight, dp) << endl;
}

int main() {
    vector<int> weight = {2, 3, 4};
    vector<int> value = {4, 5, 6};
    int maxWeight = 5;

    knapsack(weight, value, weight.size(), maxWeight);
    return 0;
}