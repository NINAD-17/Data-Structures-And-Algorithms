#include <bits/stdc++.h>
using namespace std;

// Time: O(n)
// Space: O(1)
int usingOptimizedTabulation(vector<int> &nums, int n) {
    vector<int> dp(n, 0);
    int prev2 = 0;
    int prev1 = nums[0];

    for(int i = 1; i < n; i++) {
        int incl = prev2 + nums[i];
        int excl = prev1 + 0;
        int ans = max(incl, excl);
        prev2 = prev1;
        prev1 = ans;
    }
    
    return prev1;
}


// Time: O(n)
// Space: O(n)
int usingTabulation(vector<int> &nums, int n) {
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]); 

    for(int i = 2; i < n; i++) {
        int incl = dp[i - 2] + nums[i]; 
        int excl = dp[i - 1] + 0;
        dp[i] = max(incl, excl);
    }

    return dp[n - 1];
}

// Time: O(n)
// Space: O(n) + O(n) => O(n)
int usingMemoization(vector<int> &nums, int n, vector<int> &dp) {
    // Base Case
    if(n < 0)
        return 0;

    if(n == 0)
        return nums[0];

    if(dp[n] != -1)
        return dp[n];

    int incl = usingMemoization(nums, n - 2, dp) + nums[n];
    int excl = usingMemoization(nums, n - 1, dp) + 0;

    dp[n] = max(incl, excl);
    return dp[n];
}

// Time: O(2^n)
// Space: O(n)
int usingRecursion(vector<int> &nums, int n) {
    // Base Case
    if(n < 0)
        return 0;

    if(n == 0)
        return nums[0];

    int incl = usingRecursion(nums, n - 2) + nums[n];
    int excl = usingRecursion(nums, n - 1) + 0;

    return max(incl, excl);
}


// Time: O(2^n)
// Space: O(n)
int usingRecursion_left_to_right(vector<int> &nums, int i) {
    // Base Case
    if(i >= nums.size())
        return 0;
    
    if(i == nums.size() - 1)
        return nums[nums.size() - 1];

    int incl = usingRecursion_left_to_right(nums, i + 2) + nums[i];
    int excl = usingRecursion_left_to_right(nums, i + 1) + 0;

    return max(incl, excl);
}

int maximumNonAdjacentSum(vector<int> &nums) {
    // Approach: Using Recursion
    int n = nums.size();
    int ans = usingRecursion(nums, n - 1); // Traversing from right to left // n - 1 is the last index
    cout << "Answer using recursion: " << ans << endl;

    ans = usingRecursion_left_to_right(nums, 0); // Traversing from left to right // 0 is the first index
    cout << "Answer using recursion: " << ans << endl;

    // Approach: Recursion + Memoization (Top Down)
    vector<int> dp(n, -1);
    ans = usingMemoization(nums, n - 1, dp);
    cout << "Answer using memoization: " << ans << endl;

    // Approach: Tabulation
    ans = usingTabulation(nums, n - 1);
    cout << "Answer using tabulation: " << ans << endl;

    // Approach: Optimized Tabulation
    ans = usingOptimizedTabulation(nums, n - 1);
    cout << "Answer using optimized tabulation: " << ans << endl;
}

int main() {
    vector<int> nums = {9, 9, 8, 2};

    maximumNonAdjacentSum(nums);

    return 0;
}