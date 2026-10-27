#include <bits/stdc++.h>
using namespace std;

int usingTabulation(vector<int> &cuts, int rodLen) {
    vector<int> dp(rodLen + 1, INT_MIN);
    dp[0] = 0;

    for(int i = 1; i <= rodLen; i++) {
        for(int j = 0; j < cuts.size(); j++) {
            if(i - cuts[j] >= 0)
                dp[i] = max(dp[i], 1 + dp[i - cuts[i]]);
        }
    }
} 

int usingMemoization(vector<int> &cuts, int rodLen, vector<int> &dp) {
    // Base Case
    if(rodLen == 0)
        return 0;

    if(rodLen < 0)
        return INT_MIN;

    if(dp[rodLen] != -1)
        return dp[rodLen];

    int maxAns = INT_MIN;
    for(int i = 0; i < cuts.size(); i++)
        maxAns = max(maxAns, usingMemoization(cuts, rodLen - cuts[i], dp) + 1);

    dp[rodLen] = maxAns;

    return dp[rodLen];
}

int usingRecursion(vector<int> &cuts, int rodLen) {
    // Base Case
    if(rodLen == 0)
        return 0;

    if(rodLen < 0)
        return INT_MIN;

    int maxAns = INT_MIN;
    for(int i = 0; i < cuts.size(); i++)
        maxAns = max(maxAns, usingRecursion(cuts, rodLen - cuts[i]) + 1);

    return maxAns;
}

int maxCostToCutRod(vector<int> &cuts, int rodLen) {
    cout << "Using Recursion: " << usingRecursion(cuts, rodLen) << endl;

    // Using memoization
    vector<int> dp(rodLen + 1, -1);
    cout << "Using Memoization: " << usingMemoization(cuts, rodLen, dp) << endl;
}

int main() {
    vector<int> cuts = {5, 2, 2};
    int rodLen = 7;

    maxCostToCutRod(cuts, rodLen);
    return 0;
}