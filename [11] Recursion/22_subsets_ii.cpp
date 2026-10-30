#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Leetcode: https://leetcode.com/problems/subsets-ii/description/
// Visit readme.md for visualized dry run and explanation

// Approach 2: The Loop-Based Backtracking (Most Common for Subsets)
// Time Complexity: O(n * 2^n)
// Space Complexity: O(n)
void backtrack(const vector<int> &nums, int start, vector<int> &current, vector<vector<int>> &ans) {
    // Every state visited is a valid subset
    ans.push_back(current);

    for(int i = start; i < nums.size(); i++) {
        // Skip duplicates at the same tree depth
        if(i > start && nums[i] == nums[i - 1]) {
            continue;
        }

        current.push_back(nums[i]);           // 1. DO
        backtrack(nums, i + 1, current, ans); // 2. RECURSE
        current.pop_back();                   // 3. UNDO (Backtrack)
    }
}

vector<vector<int>> subsetsWithDup2(vector<int> &nums) {
    vector<vector<int>> ans;
    vector<int> current;

    sort(nums.begin(), nums.end()); // Essential: group duplicates together
    backtrack(nums, 0, current, ans);

    return ans;
}

// Approach 1: Using the Explicit !used[i - 1] Pattern (Include / Exclude)
void solve(const vector<int> &nums, int index, vector<bool> &used, vector<int> &current, vector<vector<int>> &ans) {
    if(index >= nums.size()) {
        ans.push_back(current);
        return;
    }

    // Choice 1: Include nums[index]
    // If nums[index] == nums[index - 1] and previous was NOT included, we CANNOT include this one
    // 1. index == 0 -> include
    // 2. index == 0 false; nums[index] != nums[index - 1] = false (means equal); used[index - 1] = true (then include - else don't enter in 'if')
    if(index == 0 || nums[index] != nums[index - 1] || used[index - 1]) {
        used[index] = true;
        current.push_back(nums[index]);
        
        solve(nums, index + 1, used, current, ans);
        
        current.pop_back();
        used[index] = false;
    }

    // Choice 2: Exclude nums[index]
    solve(nums, index + 1, used, current, ans);
}

vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> ans;
    vector<int> current;
    vector<bool> used(nums.size(), false);

    sort(nums.begin(), nums.end());
    solve(nums, 0, used, current, ans);

    return ans;
}

int main() {
    vector<int> nums = {1, 2, 2};

    vector<vector<int>> ans = subsetsWithDup(nums);

    for (const vector<int> &v : ans) {
        cout << "[ ";
        for (int element : v) {
            cout << element << " ";
        }
        cout << "]\n";
    }

    return 0;
}