#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

// Leetcode: https://leetcode.com/problems/permutations-ii/description/

// Note: The Sort + used[] approach is preferred in competitive programming and interviews because it avoids the hashing and dynamic allocation overhead of unordered_set, running faster with clean $O(n)$ auxiliary space.

// Approach 2: Sort + used[] Array
// Time Complexity:
//      Number of unique permutations (U) are <= N!
//      Copying each unique permutation into ans takes O(N)
//      Therefore, O(N * U)
// Auxillary Space: O(N)
void backtrack(vector<int> &nums, vector<bool> &used, vector<int> &current, vector<vector<int>> &ans) {
    if(current.size() == nums.size()) {
        ans.push_back(current);
        return;
    }

    for(int i = 0; i < nums.size(); i++) {
        if(used[i])
            continue;

        // Skip duplicates: only use nums[i] if nums[i - 1] was already placed
        if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
            continue;
        }

        used[i] = true;
        current.push_back(nums[i]);

        backtrack(nums, used, current, ans);

        current.pop_back(); // Backtrack
        used[i] = false;
    }
}

vector<vector<int>> permuteUnique2(vector<int> &nums) {
    vector<vector<int>> ans;
    vector<int> current;
    vector<bool> used(nums.size(), false);

    sort(nums.begin(), nums.end()); // Group duplicates together
    backtrack(nums, used, current, ans);

    return ans;
}

// Approach 1: In-Place Swapping with Local Set
// Time Complexity:
//      Number of unique permutations (U) are <= N!
//      Copying each unique permutation into ans takes O(N)
//      Therefore, O(N * U)
// Auxillary Space: O(N) (or at worst O(n^2) if counting sets across all active frames, but bounded by n unique values)
void backtrack(vector<int> &nums, int index, vector<vector<int>> &ans) {
    if(index >= nums.size()) {
        ans.push_back(nums);
        return;
    }

    // Tracks values already placed at position 'index' for this level
    unordered_set<int> seen;

    for(int j = index; j < nums.size(); j++) {
        // If nums[j] was already placed at 'index' in this loop, skip it
        if(seen.find(nums[j]) != seen.end()) {
            continue;
        }

        seen.insert(nums[j]);

        swap(nums[index], nums[j]);
        backtrack(nums, index + 1, ans);
        swap(nums[index], nums[j]); // Backtrack
    }
}

vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<vector<int>> ans;
    backtrack(nums, 0, ans);
    return ans;
}

int main() {
    vector<int> nums = {1, 1, 2};

    vector<vector<int>> ans = permuteUnique(nums);

    for(vector<int> &v: ans) {
        for(int element: v) {
            cout << element << " ";
        }
        cout << endl;
    }

    return 0;
}