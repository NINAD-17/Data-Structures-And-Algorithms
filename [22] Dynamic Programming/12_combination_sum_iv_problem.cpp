#include <bits/stdc++.h>
using namespace std;

// There will be an array of values and a target. We've to make target value by taking combinations of value from array.
// Ex - arr[1, 2, 5] and target = 5
//      combinations can be 1 + 1 + 1 + 1 + 1, 1 + 1 + 1 + 2, 2 + 2 + 1, 5, etc

int usingTabulation(vector<int> &nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for(int i = 1; i <= target; i++) {
        for(int j = 0; j < nums.size(); j++) {
            if(i - nums[j] >= 0)
                dp[i] += dp[i - nums[j]];
        }
    }

    return dp[target];
}

int usingMemoization(vector<int> &nums, int target, vector<int> &dp) {
    if(target < 0)
        return 0;

    if(target == 0)
        return 1;

    if(dp[target] != -1)
        return dp[target];

    int ans = 0;
    for(int i = 0; i < nums.size(); i++)
        ans += usingMemoization(nums, target - nums[i], dp);

    dp[target] = ans;
    return dp[target];
}

int usingRecursion(vector<int> &nums, int target) {
    if(target < 0)
        return 0;

    if(target == 0)
        return 1;

    int ans = 0;
    for(int i = 0; i < nums.size(); i++)
        ans += usingRecursion(nums, target - nums[i]);

    return ans;
}

int findWays(vector<int> &nums, int target) {
    cout << usingRecursion(nums, target) << endl;

    vector<int> dp(target + 1, -1);
    cout << usingMemoization(nums, target, dp) << endl;

    cout << usingTabulation(nums, target) << endl;
}

int main() {
    vector<int> nums = {1, 2, 5};
    int target = 5;

    findWays(nums, target);
    
    return 0;
}