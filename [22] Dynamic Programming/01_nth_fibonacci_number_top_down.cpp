#include <bits/stdc++.h>
using namespace std;

// Method: Top-Down (Recursion + Memoization)

// Time Complexity: O(n)
// Space Complexity: O(n)
//  - O(n) for vector space
//  - O(n) for n recursive calls

int fib(int n, vector<int> &dp) {
    // Base Case
    if(n <= 1) {
        return n;
    }

    // Check if fibonacci already exist or not
    if(dp[n] != -1) {
        return dp[n];
    }

    // Memoized calculated fibonacci
    dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
    return dp[n];
}

int main() {
    int n = 6;
    // cin >> n;

    // Create DP Array
    vector<int> dp(n + 1);

    // Initialize DP with -1 values
    for(int i = 0; i <= n; i++) {
        dp[i] = -1;
    }

    cout << fib(n, dp) << endl;
    return 0;
}