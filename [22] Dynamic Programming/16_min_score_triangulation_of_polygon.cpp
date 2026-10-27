#include <bits/stdc++.h>
using namespace std;

int usingTabulation(vector<int> &values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int i = n - 1; i >= 0; i--) {
        for(int j = i + 2; j < n; j++) {
            int ans = INT_MAX;
            for(int k = i + 1; k < j; k++)
                ans = min(ans, (values[i] * values[j] * values[k]) + dp[i][k] + dp[k][j]);
            
            dp[i][j] = ans;
        }
    }

    return dp[0][n - 1];
}

int usingMemoization(vector<int> &values, int i, int j, vector<vector<int>> &dp) {
    // Base Case: Only 2 vertex present then we can't make triangle.
    if(i + 1 == j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int ans = INT_MAX;
    for(int k = i + 1; k < j; k++)
        ans = min(ans, (values[i] * values[j] * values[k]) + usingMemoization(values, i, k, dp) + usingMemoization(values, k, j, dp));

    return dp[i][j] = ans;
}

int usingRecursion(vector<int> &values, int i, int j) {
    // Base Case: Only 2 vertex present then we can't make triangle.
    if(i + 1 == j)
        return 0;

    int ans = INT_MAX;
    for(int k = i + 1; k < j; k++) {
        ans = min(ans, (values[i] * values[j] * values[k]) + usingRecursion(values, i, k) + usingRecursion(values, k, j));
    }

    return ans;
}

int minScoreTriangulation(vector<int> &values) {
    int n = values.size();
    cout << "Using Recursion: " << usingRecursion(values, 0, n - 1) << endl; // 0 is the first index and n - 1 is the last index. These 2 vertex makes a base.

    vector<vector<int>> dp(n, vector<int> (n, -1));
    cout << "Using Memoization: " << usingMemoization(values, 0, n - 1, dp) << endl;

    cout << "Using Tabulation: " << usingTabulation(values) << endl;
}

int main() {
    vector<int> values = {1, 2, 3};

    minScoreTriangulation(values);

    return 0;
}