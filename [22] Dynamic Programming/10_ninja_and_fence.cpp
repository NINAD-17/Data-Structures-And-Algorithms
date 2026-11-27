#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

// Problem: Painting Fence Algorithm
// In how many ways we can paint the post such that not more than 2 consecutive posts have same color.

int add(int a, int b) {
    return (a % MOD + b % MOD) % MOD;
}

int mult(int a, int b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

// Time: O(n)
// Space: O(1)
int tabulationSpaceOptimized(int n, int k) {
    int prev2 = k;
    int prev1 = add(k, mult(k, k - 1));

    for(int i = 3; i <= n; i++) {
        int ans = add(mult(prev2, k - 1), mult(prev1, k - 1));
        prev2 = prev1;
        prev1 = ans;
    }

    return prev1;
}

// Time: O(n)
// Space: O(n)
int tabulation(int n, int k) {
    vector<int> dp(n + 1, 0);
    dp[1] = k;
    dp[2] = add(k, mult(k, k - 1));

    for(int i = 3; i <= n; i++)
        dp[i] = add(mult(dp[i - 2], k - 1), mult(dp[i - 1], k - 1));

    return dp[n];
}

// Time: O(n)
// Space: O(n)
int memoization(int n, int k, vector<int> &dp) {
    if(n == 1) return k;

    if(n == 2) return add(k, mult(k, k - 1));

    if(dp[n] != -1) return dp[n];

    dp[n] = add(mult(memoization(n - 2, k, dp), k - 1), mult(memoization(n - 1, k, dp), k - 1));

    return dp[n];
}

// Time: O(2^n)
// Space: O(n)
int recursion(int n, int k) {
    if(n == 1) return k;

    if(n == 2) return add(k, mult(k, k - 1));

    int ans = add(mult(recursion(n - 2, k), k - 1), mult(recursion(n - 1, k), k - 1));

    return ans;
}

int numberOfWays(int n, int k) {
    cout << "Recursion: " << recursion(n, k) << endl;

    vector<int> dp(n + 1, -1);
    cout << "Memoization: " << memoization(n, k, dp) << endl;

    cout << "Tabulation: " << tabulation(n, k) << endl;

    cout << "Tabulation Space Optimized: " << tabulationSpaceOptimized(n, k) << endl;
}

int main() {
    int n = 3, k = 2; // N = number of posts, K = number of colors

    numberOfWays(n, k);

    return 0;
}