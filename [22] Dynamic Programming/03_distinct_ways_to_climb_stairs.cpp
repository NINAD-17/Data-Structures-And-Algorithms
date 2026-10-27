#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

// Time: O(n)
// Space: O(1)
int usingTabulation_SpaceOptimized(long long nStairs) {
    int prev2 = 1;
    int prev1 = 1;

    for(int i = 2; i <= nStairs; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int usingTabulation_fromZero(long long nStairs) {
    vector<int> dp(nStairs + 2, 0); // +2 to handle dp[nStairs+1] safely
    dp[nStairs] = 1; // if you’re at the destination, 1 way
    dp[nStairs + 1] = 0; // Invalid

    for(int i = nStairs - 1; i >= 0; i--) {
        dp[i] = dp[i + 1] + dp[i + 2];
    }

    return dp[0]; // ways from stair 0 to reach nStair
}

// Time: O(n)
// Space: O(n)
int usingTabulation(long long nStairs) {
    vector<int> dp(nStairs + 1);

    dp[0] = 1;
    dp[1] = 1;

    for(int i = 2; i <= nStairs; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[nStairs];
}

// Time: O(n)
// Space: O(n) recursion stack + O(n) dp array = O(n)
int usingMemoization(long long nStairs, int i, vector<int> dp) {
    if(i == nStairs)
        return 1; // if your current stair is destination stair then number of ways to reach it is 1

    if(i > nStairs)
        return 0; // invalid case

    if(dp[i] != -1)
        return dp[i];

    dp[i] = usingMemoization(nStairs, i + 1, dp) + usingMemoization(nStairs, i + 2, dp);
    return dp[i];
}

int usingMemoization_fromNthStair(long long nStairs, vector<int> &dp) {
    // Base cases
    if(nStairs == 0) return 1; // one way: do nothing
    if(nStairs == 1) return 1; // one way: single step

    if(dp[nStairs] != -1)
        return dp[nStairs];
    
    // Recursive relation: ways to reach n = ways to reach (n-1) + ways to reach (n-2)
    return dp[nStairs] = (usingMemoization_fromNthStair(nStairs - 1, dp) + usingMemoization_fromNthStair(nStairs - 2, dp)) % MOD;
}

// Time: O(2^n)
// Space: O(n)
int usingRecursion(long long nStairs, int i) {
    if(i == nStairs)
        return 1; // if your current stair is destination stair then number of ways to reach it is 1

    if(i > nStairs)
        return 0; // invalid case

    return (usingRecursion(nStairs, i + 1) + usingRecursion(nStairs, i + 2)) % MOD;
    // Ex - f(0) = f(n + 1) + f(n + 2); it means from 0th stairs to reach nth, number of ways will be f(1) from 1st stairs num of ways + f(2) from 2nd stairs num of ways 
}

// Time: O(2^n)
// Space: O(n)
int usingRecursion_fromNthStair(long long nStairs) {
    // Base cases
    if(nStairs == 0) return 1; // one way: do nothing
    if(nStairs == 1) return 1; // one way: single step

    // Recursive relation: ways to reach n = ways to reach (n-1) + ways to reach (n-2)
    return (usingRecursion_fromNthStair(nStairs - 1) + usingRecursion_fromNthStair(nStairs - 2)) % MOD;
}

int countDistinctWaysToClimbStairs(long long nStairs) {
    int ans = usingRecursion(nStairs, 0);
    cout << "Number of ways to climb stairs using 1 and 2 steps is: " << ans << endl;

    ans = usingRecursion_fromNthStair(nStairs);
    cout << "Number of ways to climb stairs using 1 and 2 steps is: " << ans << endl;

    vector<int> dp(nStairs + 1, -1);
    ans = usingMemoization(nStairs, 0, dp);
    cout << "Using Memoization: " << ans << endl;

    ans = usingTabulation(nStairs);
    cout << "Using Tabulation: " << ans << endl;

    ans = usingTabulation_SpaceOptimized(nStairs);
    cout << "Using Tabulation (Space Optimized): " << ans << endl;
}

int main() {
    int nStairs = 4;

    countDistinctWaysToClimbStairs(nStairs);
    return 0;
}