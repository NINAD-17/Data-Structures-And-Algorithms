#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

// Min Cost Climbing Stairs
// You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.
// You can either start from the step with index 0, or the step with index 1.
// Return the minimum cost to reach the top of the floor.

// Example:
// - Input: cost = [10,15,20]
// - Output: 15
// - Explanation: You will start at index 1.
//      Pay 15 and climb two steps to reach the top.
//      The total cost is 15.

// Summary:
// - We can start from 0th or 1st stair.
// - We've to pay cost, only then we can move 1 or 2 steps ahead.
// - Return min cost to reach top floor.


// Time: O(n)
// Space: O(1)
int usingTabulation_spaceOptimized(vector<int> &cost, int n) {
    int prev2 = cost[0];
    int prev1 = cost[1];

    for(int i = 2; i < n; i++) {
        int curr = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = curr;
    }

    return min(prev1, prev2);
}

// Time: O(n)
// Space: O(n)
int usingTabulation(vector<int> &cost, int n) {
    vector<int> dp(n + 1);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for(int i = 2; i < n; i++)
        dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);

    return min(dp[n - 1], dp[n - 2]);
}

// Time: O(n)
// Space: O(n) recursion stack + O(n) dp array
int usingMemoization(vector<int> &cost, int n, vector<int> &dp) {
    // base case
    if(n == 0)
        return cost[0];
    if(n == 1)
        return cost[1];

    if(dp[n] != -1)
        return dp[n];

    dp[n] = cost[n] + min(usingMemoization(cost, n - 1, dp), usingMemoization(cost, n - 2, dp));
    return dp[n];
}

// Time: O(2^n)
// Space: O(n)
int usingRecursion(vector<int> &cost, int n) {
    // base case
    if(n == 0)
        return cost[0];
    if(n == 1)
        return cost[1];

    int ans = cost[n] + min(usingRecursion(cost, n - 1), usingRecursion(cost, n - 2));
    return ans;
}

int solveFromZero(vector<int> &cost, int i, int n) {
    // Base case: reached the top
    if(i >= n) return 0;

    // Pay cost at current stair, then move 1 or 2 steps
    int oneStep = cost[i] + solveFromZero(cost, i+1, n);
    int twoStep = cost[i] + solveFromZero(cost, i+2, n);

    return min(oneStep, twoStep);
}

int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();

    int ans = min(usingRecursion(cost, n - 1), usingRecursion(cost, n - 2));
    cout << "min cost of climbing stairs using recursion: " << ans << endl;

    vector<int> dp(n + 1, -1);
    ans = min(usingMemoization(cost, n - 1, dp), usingMemoization(cost, n - 2, dp));
    cout << "using memoization: " << ans << endl;

    ans = usingTabulation(cost, n);
    cout << "using tabulation: " << ans << endl;

    cout << "using tabulation space optimized: " << usingTabulation_spaceOptimized(cost, n) << endl;

    // return min(solveFromZero(cost, 0, n), solveFromZero(cost, 1, n));
}

int main() {
    vector<int> cost = {10, 15, 20};
    
    minCostClimbingStairs(cost);
    return 0;
}