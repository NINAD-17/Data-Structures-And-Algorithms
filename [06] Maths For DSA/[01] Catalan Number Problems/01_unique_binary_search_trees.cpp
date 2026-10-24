#include <bits/stdc++.h>
using namespace std;

// Leetcode: https://leetcode.com/problems/unique-binary-search-trees/description/

// Time Complexity: O(n^2)
// Space Complexity: O(n)
int numTrees(int n) {
    // dp[i] stores the number of structurally unique BSTs with i nodes
    vector<int> dp(n + 1, 0);

    // Base cases:
    // 0 nodes -> 1 empty tree
    // 1 node  -> 1 single-node tree
    dp[0] = 1;
    dp[1] = 1;

    // Fill DP table from 2 up to n nodes
    for(int i = 2; i <= n; i++) {
        // Pick each possible number of nodes 'j' to go into the left subtree
        // The right subtree naturally receives (i - 1 - j) nodes
        for(int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }

    return dp[n];
}

int main() {
    int n = 5;

    cout << "Number of unique binary trees which can be formed from " << n << " nodes is " << numTrees(n) << endl;

    return 0;
}