#include <bits/stdc++.h>
using namespace std;

// Question: We've an input array of coins [1, 2, 5] and those coins are present in an infinite supply. 
//      By using those coins we've to find minimum number of coins to make that amount. In our example the answer is [5 + 5 + 1].
//      If we can't make the target then return -1.

// Example: [1, 2, 3] and amount to make is 7.
//      i. [1 + 1 + .... + 1] (seven times 1)
//      ii. [2 + 2 + 2 + 1]
//      iii. [3 + 3 + 1] (this is the minimum answer)

// Approach: Tabulation
// Time: O(n) * O(coins.size())
// Space: O(n)
int usingTabulation(vector<int> &coins, int targetAmt) {
    // dp[i] = minimum number of coins required to make amount i  
    vector<int> dp(targetAmt + 1, INT_MAX);
    dp[0] = 0; // Base case: 0 coins needed to make amount 0

    // Fill dp array for all amounts from 1 to targetAmt
    for(int i = 1; i <= targetAmt; i++) {
        // Solve every amount figure from 1 to targetAmt
        for(int j = 0; j < coins.size(); j++) {
            // For each amount utilize all the coins to find an answer
            if(i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX) {
                dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
            }
        }
    }

    if(dp[targetAmt] == INT_MAX) {
        return -1;
    }

    return dp[targetAmt];
}

// Approach: Memoization
// Time: O(n) * O(coins.size())
// Space: O(n) + O(n)
int usingMemoization(vector<int> &coins, int targetAmt, vector<int> &dp) {
    // Base Case 1: If target becomes 0, no coins are needed.
    if(targetAmt == 0) {
        return 0; // 0 coins
    }

    // Base Case 2: If target becomes negative, this path is invalid.
    // Return INT_MAX as a "flag" for impossible solution.
    if(targetAmt < 0) {
        return INT_MAX;
    }

    if(dp[targetAmt] != -1)
        return dp[targetAmt];

    // Variable to track the minimum coins among all choices.
    int mini = INT_MAX;

    // Try every coin one by one.
    for(int i = 0; i < coins.size(); i++) {
        // Recursive call: reduce target by current coin value.
        int ans = usingMemoization(coins, targetAmt - coins[i], dp);

        // If recursion returned a valid solution (not INT_MAX),
        // then total coins = 1 (the coin we just used) + ans (coins for remainder).
        if(ans != INT_MAX) {
            mini = min(mini, 1 + ans);
        }
    }

    dp[targetAmt] = mini;

    // Return the minimum coins found for this targetAmt.
    return dp[targetAmt];
}

// Approach: Recursive Brute Force
// Time: O(2^n)
// Space: O(n)
int usingRecursion(vector<int> &coins, int targetAmt) {
    // Base Case 1: If target becomes 0, no coins are needed.
    if(targetAmt == 0) {
        return 0; // 0 coins
    }

    // Base Case 2: If target becomes negative, this path is invalid.
    // Return INT_MAX as a "flag" for impossible solution.
    if(targetAmt < 0) {
        return INT_MAX;
    }

    // Variable to track the minimum coins among all choices.
    int mini = INT_MAX;

    // Try every coin one by one.
    for(int i = 0; i < coins.size(); i++) {
        // Recursive call: reduce target by current coin value.
        int ans = usingRecursion(coins, targetAmt - coins[i]);

        // If recursion returned a valid solution (not INT_MAX),
        // then total coins = 1 (the coin we just used) + ans (coins for remainder).
        if(ans != INT_MAX) {
            mini = min(mini, 1 + ans);
        }
    }

    // Return the minimum coins found for this targetAmt.
    return mini;
}

int minimumNumCoins(vector<int> &coins, int targetAmt) {
    int ans = usingRecursion(coins, targetAmt);
    
    // If answer is INT_MAX, it means no valid solution exists.
    if(ans == INT_MAX) {
        return -1;
    } else {
        cout << "Minimum number of coins required: " << ans << endl; // Print minimum number of coins.
    }

    vector<int> dp(targetAmt + 1, -1);
    ans = usingMemoization(coins, targetAmt, dp);
    if(ans == INT_MAX) {
        return -1;
    } else {
        cout << "Minimum number of coins required (using Memoization): " << ans << endl; // Print minimum number of coins.
    }
}

int main() {
    vector<int> coins = {1, 3, 5};
    int targetAmt = 11;

    minimumNumCoins(coins, targetAmt);

    return 0;
}