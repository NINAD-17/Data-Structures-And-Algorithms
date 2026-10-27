#include <bits/stdc++.h>
using namespace std;

int usingTabulation(vector<vector<int>> &mat, int &maxi) {
    int row = mat.size();
    int col = mat[0].size();

    vector<vector<int>> dp(row + 1, vector<int> (col + 1, 0));

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

int usingMemoization(vector<vector<int>> &mat, int i, int j, int maximum, vector<vector<int>> &dp) {
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
    cout << usingRecursion(mat, 0, 0, maximum) << endl;

    maximum = 0;
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << usingMemoization(mat, 0, 0, maximum, dp) << endl;

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