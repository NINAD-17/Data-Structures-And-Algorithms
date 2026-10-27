#include <bits/stdc++.h>
using namespace std;

// Minimum Sideways Jumps: https://leetcode.com/problems/minimum-sideway-jumps/description/

// Note: dp[i][j] means from (i, j)th position to reach destination (1, n)/(2, n)/(3, n) how many minimum side ways jumps are required

int usingTabulation(vector<int> &obstacles, int totalLanes, int currLane, int pos) {
    int n = obstacles.size() - 1;
    vector<vector<int>> dp(totalLanes + 1, vector<int> (obstacles.size(), INT_MAX));

    dp[0][n] = 0;
    dp[0][n] = 0;
    dp[0][n] = 0;
    dp[0][n] = 0;

    for(int pos = n - 1; pos >= 0; pos--) {
        for(int lane = 1; lane <= 3; lane++) {
            if(obstacles[pos + 1] != currLane) {
                dp[lane][pos] = dp[currLane][pos + 1];
            } else {
                // Jump sideway as there's an obstacle on next position of current lane.
                int ans = INT_MAX;
                for(int i = 1; i <= 3; i++) { // 3 choices of lane to jump
                    if(currLane != i && obstacles[pos] != i)
                        ans = min(ans, 1 + dp[i][pos + 1]);
                }
                dp[lane][pos] = ans;
            }
        }
    }

    return min(dp[2][0], min(1 + dp[1][0], 1 + dp[3][0]));
}

int usingMemoization(vector<int> &obstacles, int currLane, int pos, vector<vector<int>> &dp) { // pos is current position
    // Base Case
    if(pos == obstacles.size() - 1)
        return 0;

    if(dp[currLane][pos] != -1)
        return dp[currLane][pos];

    if(obstacles[pos + 1] != currLane) {
        dp[currLane][pos] = usingMemoization(obstacles, currLane, pos + 1, dp);
        return dp[currLane][pos];
    } else {
        // Jump sideway as there's an obstacle on next position of current lane.
        int ans = INT_MAX;
        for(int i = 1; i <= 3; i++) { // 3 choices of lane to jump
            if(currLane != i && obstacles[pos] != i)
                ans = min(ans, 1 + usingMemoization(obstacles, i, pos, dp));
        }
        dp[currLane][pos] = ans;
        return dp[currLane][pos];
    }
}

int usingRecursion(vector<int> &obstacles, int currLane, int pos) { // pos is current position
    // Base Case
    if(pos == obstacles.size() - 1)
        return 0;

    if(obstacles[pos + 1] != currLane) {
        return usingRecursion(obstacles, currLane, pos + 1);
    } else {
        // Jump sideway as there's an obstacle on next position of current lane.
        int ans = INT_MAX;
        for(int i = 1; i <= 3; i++) { // 3 choices of lane to jump
            if(currLane != i && obstacles[pos] != i)
                ans = min(ans, 1 + usingRecursion(obstacles, i, pos));
        }
        return ans;
    }
}

int minSideJumps(vector<int> &obstacles, int totalLanes) {
    cout << usingRecursion(obstacles, 2, 0) << endl;

    vector<vector<int>> dp(totalLanes + 1, vector<int>(obstacles.size(), -1));
    cout << usingMemoization(obstacles, 2, 0, dp) << endl;

    cout << usingTabulation(obstacles, totalLanes, 2, 0) << endl;
}

int main() {
    vector<int> obstacles = {0, 1, 2, 3, 0}; // 0 means obstacle on 0th lane (not on road) on ith position. 1 means on ith position at lane 1 there's an obstacle.
    int totalLanes = 3;


    return 0;
}