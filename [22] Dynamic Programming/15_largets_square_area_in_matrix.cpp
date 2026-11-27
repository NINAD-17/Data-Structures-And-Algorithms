#include <bits/stdc++.h>
using namespace std;

// Maximal Square
// Leetcode: https://leetcode.com/problems/maximal-square/
// To understand difference between Memoization and Tabulation approach - read README.md

// Time Complexity: O(row * col)
// Space Complexity: O(col)
int usingTabulationSpaceOptimized(vector<vector<int>> &matrix, int &maxSide) {
    int row = matrix.size();
    int col = matrix[0].size();

    vector<int> next(col + 1, 0);
    vector<int> curr(col + 1, 0);

    for(int i = row - 1; i >= 0; i--) {
        for(int j = col - 1; j >= 0; j--) {
            int right = curr[j + 1];
            int diagonal = next[j + 1];
            int down = next[j];

            if(matrix[i][j] == '1') {
                curr[j] = 1 + min({right, diagonal, down});
                maxSide = max(maxSide, curr[j]);
            } else {
                curr[j] = 0;
            }
        }

        next = curr;
    }

    return maxSide * maxSide;
}

// Time Complexity: O(row * col)
//                  Two nested loops visit each of the row * col cells exactly once and do O(1) operations per cell.
// Space Complexity: O(row * col)
//                  Uses a 2D vector dp of size (row + 1) * (col + 1) with 0 recursion stack space.
int usingTabulation(vector<vector<int>> &mat, int &maxi) {
    int row = mat.size();
    int col = mat[0].size();

    vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));

    for(int i = row - 1; i >= 0; i--) {
        for(int j = col - 1; j >= 0; j--) {
            int right = dp[i][j + 1];
            int diag = dp[i + 1][j + 1];
            int bottom = dp[i + 1][j];

            if(mat[i][j] == 1) {
                dp[i][j] = 1 + min(right, min(diag, bottom));
                maxi = max(maxi, dp[i][j]);
            } else {
                dp[i][j] = 0;
            }
        }
    }

    return dp[0][0];
}

// Time Complexity: O(row * col)
//                  There are row * col distinct subproblems (i, j). Each subproblem does O(1) constant work (calculates min of 3 cached values). Once computed, it is stored in dp[i][j] and never calculated again.
// Space Complexity: O(row * col)
//                  - O(row * col) to store the 2D DP table.
//                  - O(row + col) auxiliary stack space for recursion.
//                  - Total space: O(row * col).
int usingMemoization(vector<vector<int>> &mat, int i, int j, int &maximum, vector<vector<int>> &dp) {
    if(i >= mat.size() || j >= mat[0].size())
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int right = usingMemoization(mat, i, j + 1, maximum, dp);
    int diagonal = usingMemoization(mat, i + 1, j + 1, maximum, dp);
    int down = usingMemoization(mat, i + 1, j, maximum, dp);

    if(mat[i][j] == 1) {
        dp[i][j] = 1 + min(right, min(diagonal, down));
        maximum = max(maximum, dp[i][j]);
        return dp[i][j];
    } else {
        return dp[i][j] = 0;
    }
}

// Time Complexity: O(3^(row * col))
//                  Every cell makes up to 3 recursive branches (Right, Diagonal, Down). Without memoization, cells are recomputed an exponential number of times.
// Space Complexity: O(row + col)
//                  The maximum recursion call stack depth is the longest path from (0, 0) to (R - 1, C - 1), which is at most $R + C$ frames.
int usingRecursion(vector<vector<int>> &mat, int i, int j, int &maximum) {
    if(i >= mat.size() || j >= mat[0].size())
        return 0;

    int right = usingRecursion(mat, i, j + 1, maximum);
    int diagonal = usingRecursion(mat, i + 1, j + 1, maximum);
    int down = usingRecursion(mat, i + 1, j, maximum);

    if(mat[i][j] == 1) {
        int ans = 1 + min(right, min(diagonal, down));
        maximum = max(maximum, ans);
        return ans;
    } else {
        return 0;
    }
}

int maxSquare(int n, int m, vector<vector<int>> &mat) {
    int maximum = 0;
    usingRecursion(mat, 0, 0, maximum);
    cout << maximum << endl;

    maximum = 0;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    usingMemoization(mat, 0, 0, maximum, dp);
    cout << maximum << endl;

    int maxi = 0;
    cout << usingTabulation(mat, maxi) << endl;
}

int main() {
    vector<vector<int>> mat = {{1, 1, 1, 1},
                               {1, 1, 1, 1},
                               {1, 1, 0, 1},
                               {1, 1, 1, 1}};

    int n = 4, m = 4;

    maxSquare(n, m, mat);

    return 0;
}