#include <bits/stdc++.h>
using namespace std;

// Perfect Squares Problem
// Find minimum number of squares of any number that sums to N. How many perfect squares will need to get N.

int usingTabulation(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j * j <= n; j++) {
            int temp = j * j;

            if(i - temp >= 0)
                dp[i] = min(dp[i], 1 + dp[i - temp]);
        }
    }

    return dp[n];
}

int usingMemoization(int n, vector<int> &dp) {
    if(n == 0)
        return 0;

    if(dp[n] != -1)
        return dp[n];

    int ans = n; // max answer - as we want min
    for(int i = 1; i * i <= n; i++)
        ans = min(ans, 1 + usingMemoization(n - i * i, dp));

    dp[n] = ans;
    return dp[n];
}

int usingRecursion(int n) {
    // Base Case
    if(n == 0)
        return 0;

    int ans = n; // max answer - as we want min
    for(int i = 1; i * i <= n; i++)
        ans = min(ans, 1 + usingRecursion(n - i * i));

    return ans;
}

int minNumOfPerfectSquares(int n) {
    cout << usingRecursion(n) << endl;

    vector<int> dp(n + 1, -1);
    cout << usingMemoization(n, dp) << endl;

    cout << usingTabulation(n) << endl;
}

int main() {
    int n = 10;
    
    minNumOfPerfectSquares(n);
    
    return 0;
}