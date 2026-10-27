#include <bits/stdc++.h>
using namespace std;

// Minimum Cost for Tickets

int usingTabulation(int totalDays, vector<int> &days, vector<int> &cost) {
    vector<int> dp(totalDays + 1, INT_MAX);
    dp[totalDays] = 0;

    for(int k = totalDays - 1; k >= 0; k--) {
        // 1 Day Pass
        int option1 = cost[0] + dp[k + 1];

        // 7 Day Pass
        int i;
        for(i = k; i < totalDays && days[i] < days[k] + 7; i++);
        int option2 = cost[1] + dp[i];

        // 30 Day Pass
        for(i = k; i < totalDays && days[i] < days[k] + 30; i++);
        int option3 = cost[2] + dp[i];

        dp[k] = min(option1, option2, option3);
    }

    return dp[0];
}

int usingMemoization(int totalDays, vector<int> &days, vector<int> &cost, int index, vector<int> &dp) {
    // Base Case
    if(index >= totalDays)
        return 0;

    if(dp[index] != -1)
        return dp[index];

    // 1 Day Pass
    int option1 = cost[0] + usingRecursion(totalDays, days, cost, index + 1);

    // 7 Day Pass
    int i;
    for(i = index; i < totalDays && days[i] < days[index] + 7; i++);
    int option2 = cost[1] + usingMemoization(totalDays, days, cost, i, dp); // i is the index after 7 days

    // 30 Day Pass
    for(i = index; i < totalDays && days[i] < days[index] + 30; i++);
    int option3 = cost[2] + usingMemoization(totalDays, days, cost, i, dp);

    dp[index] = min(option1, option2, option3);
    return dp[index];
}

int usingRecursion(int totalDays, vector<int> &days, vector<int> &cost, int index) {
    // Base Case
    if(index >= totalDays)
        return 0;

    // 1 Day Pass
    int option1 = cost[0] + usingRecursion(totalDays, days, cost, index + 1);

    // 7 Day Pass
    int i;
    for(i = index; i < totalDays && days[i] < days[index] + 7; i++);
    int option2 = cost[1] + usingRecursion(totalDays, days, cost, i); // i is the index after 7 days

    // 30 Day Pass
    for(i = index; i < totalDays && days[i] < days[index] + 30; i++);
    int option3 = cost[2] + usingRecursion(totalDays, days, cost, i);

    return min(option1, option2, option3);
}

int minimumCostForTickets(int totalDays, vector<int> &days, vector<int> &cost) {
    cout << usingRecursion(totalDays, days, cost, 0) << endl;

    vector<int> dp(totalDays + 1, -1);
    cout << usingMemoization(totalDays, days, cost, 0, dp) << endl;

    cout << usingTabulation(totalDays, days, cost) << endl;
}

int main() {

    
    return 0;
}