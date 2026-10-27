#include <bits/stdc++.h>
using namespace std;

int usingTabulation(vector<int> &satisfaction) {
    int n = satisfaction.size();
    vector<vector<int>> dp(n + 1, vector<int> (n + 1, 0));

    for(int index = n - 1; index >= 0; index--) {
        for(int time = index; time >= 0; time--) {
            int include = satisfaction[index] * (time + 1) + dp[index + 1][time + 1];
            int exclude = 0 + dp[index + 1][time];

            dp[index][time] = max(include, exclude);
        }
    }

    return dp[0][0];
}

int usingMemoization(vector<int> &satisfaction, int index, int time, vector<vector<int>> &dp) {
    // Base Case
    if(index == satisfaction.size()) 
        return 0;
    
    if(dp[index][time] != -1)
        return dp[index][time];

    int include = satisfaction[index] * (time + 1) + usingMemoization(satisfaction, index + 1, time + 1, dp);
    int exclude = 0 + usingMemoization(satisfaction, index + 1, time, dp);

    return dp[index][time] = max(include, exclude);
}

int usingRecursion(vector<int> &satisfaction, int index, int time) {
    // Base Case
    if(index == satisfaction.size()) 
        return 0;

    int include = satisfaction[index] * (time + 1) + usingRecursion(satisfaction, index + 1, time + 1);
    int exclude = 0 + usingRecursion(satisfaction, index + 1, time);

    return max(include, exclude);
}

int maxSatisfaction(vector<int> &satisfaction) {
    sort(satisfaction.begin(), satisfaction.end());
    cout << usingRecursion(satisfaction, 0, 0) << endl;

    int n = satisfaction.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    cout << usingMemoization(satisfaction, 0, 0, dp) << endl;

    cout << usingTabulation(satisfaction) << endl;
}

int main() {
    // Satisfaction level of dishes from 0th dish to nth dish
    vector<int> satisfaction = {-1, -8, 0, 5, -9};

    maxSatisfaction(satisfaction);
    return 0;
}