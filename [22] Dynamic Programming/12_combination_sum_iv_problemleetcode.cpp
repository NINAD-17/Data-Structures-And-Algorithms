#include <bits/stdc++.h>
using namespace std;

// Leetcode: https://leetcode.com/problems/combination-sum-iv/description/

// There will be an array of values and a target. We've to make target value by taking combinations of value from array.
// Ex - arr[1, 2, 5] and target = 5
//      combinations can be 1 + 1 + 1 + 1 + 1, 1 + 1 + 1 + 2, 2 + 2 + 1, 5, etc

// ------- Follow Up Question From Leetcode --------
int combinationSum4WithNegatives(vector<int> &nums, int target, int maxLen) {
    // dp[len][sum] = number of combinations of length 'len' that sum to 'sum'
    // We use an unordered_map for the sum because negative sums are possible.
    vector<unordered_map<int, long long>> dp(maxLen + 1);

    // Base case: length 0 produces sum 0 in exactly 1 way (empty combination)
    dp[0][0] = 1;

    long long totalWays = 0;

    for(int len = 1; len <= maxLen; len++) {
        for(auto &[prevSum, count] : dp[len - 1]) {
            for(int num : nums) {
                int newSum = prevSum + num;
                dp[len][newSum] += count;
            }
        }

        // Add combinations of this length that reach the target
        if(dp[len].count(target)) {
            totalWays += dp[len][target];
        }
    }

    return totalWays;
}
// -------------------------------------------------

int usingTabulation2(vector<int> &nums, int target) {
    vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1; // 1 way to make sum 0: empty set

    for(int i = 1; i <= target; i++) {
        for(int num : nums) {
            if(i >= num) {
                dp[i] += dp[i - num];
            }
        }
    }

    return (int)dp[target];
}

int usingTabulation(vector<int> &nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for(int tar = 1; tar <= target; tar++) {
        for(int numIndex = 0; numIndex < nums.size(); numIndex++) {
            if(tar - nums[numIndex] >= 0) {
                if(dp[tar] <= INT_MAX - dp[tar - nums[numIndex]]) {
                    dp[tar] += dp[tar - nums[numIndex]];
                }
            }
        }
    }

    return dp[target];
}

unsigned int usingMemoization2(vector<int> &nums, int target, vector<unsigned int> &dp, vector<bool> &visited) {
    if(target == 0)
        return 1;

    if(visited[target])
        return dp[target];

    unsigned int ans = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(target >= nums[i]) {
            ans += usingMemoization2(nums, target - nums[i], dp, visited);
        }
    }

    visited[target] = true;
    return dp[target] = ans;
}

int usingMemoization(vector<int> &nums, int target, vector<int> &dp) {
    if(target == 0)
        return 1;

    if(dp[target] != -1)
        return dp[target];

    int ans = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(target >= nums[i]) {
            int ways = usingMemoization(nums, target - nums[i], dp);

            // Only add if it doesn't cause signed overflow
            if(ans <= INT_MAX - ways) {
                ans += ways;
            }
        }
    }

    return dp[target] = ans;
}

int findWays(vector<int> &nums, int target) {
    vector<int> dp(target + 1, -1);
    cout << usingMemoization(nums, target, dp) << endl;

    vector<unsigned int> dp2(target + 1, 0);
    vector<bool> visited(target + 1, false);
    cout << (int)usingMemoization2(nums, target, dp2, visited) << endl;

    cout << usingTabulation(nums, target) << endl;
}

int main() {
    vector<int> nums = {1, 2}; // Ex. - {1, 2, 5}
    int target = 3;            // Ex. - 5

    findWays(nums, target);

    return 0;
}