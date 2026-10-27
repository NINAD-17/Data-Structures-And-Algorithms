#include <bits/stdc++.h>
using namespace std;

int usingMemoization(vector<int> &slices, int index, int endIndex, int n, vector<vector<int>> &dp) {
    // Base Case: You ate all your pizza slices (totalSlices/3)
    if(n == 0 || index >= endIndex)
        return 0; // Can't eat more

    if(dp[index][n] != -1)
        return dp[index][n];

    int include = slices[index] + usingMemoization(slices, index + 2, endIndex, n - 1, dp);
    int exclude = 0 + usingMemoization(slices, index + 1, endIndex, n, dp);

    return dp[index][n] = max(include, exclude);
}

int usingRecursion(vector<int> &slices, int index, int endIndex, int n) {
    // Base Case: You ate all your pizza slices (totalSlices/3)
    if(n == 0 || index >= endIndex)
        return 0; // Can't eat more

    int include = slices[index] + usingRecursion(slices, index + 2, endIndex, n - 1);
    int exclude = 0 + usingRecursion(slices, index + 1, endIndex, n);

    return max(include, exclude);
}

int maxSizeSlices(vector<int> &slices, int totalSlices) {
    // Recursion
    int k = totalSlices;
    int case1 = usingRecursion(slices, 0, k - 2, k/3);
    int case2 = usingRecursion(slices, 1, k - 1, k/3);
    cout << max(case1, case2) << endl;

    // Memoization
    vector<vector<int>> dp1(k, vector<int> (k, -1));
    case1 = usingMemoization(slices, 0, k - 2, k/3, dp1);

    vector<vector<int>> dp2(k, vector<int> (k, -1));
    case2 = usingMemoization(slices, 1, k - 1, k/3, dp2);
    cout << max(case1, case2) << endl;
}

int main() {
    vector<int> slices = {1, 2, 3, 4, 5, 6};
    int totalSlices = slices.size();

    maxSizeSlices(slices, totalSlices);

    return 0;
}