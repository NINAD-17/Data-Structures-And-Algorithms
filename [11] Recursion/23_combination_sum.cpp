#include <algorithm>
#include <vector>
using namespace std;

// Leetcode: https://leetcode.com/problems/combination-sum/description/

// Approach 2: The Loop-Based Backtracking Pattern (Standard Interview Style)
// Time Complexity: O(2^T * K) ... where T = taret/min(candidate) and K is the avg length of valid combination copied into ans
// Auxillary Space: O(T)
void backtrack(int start, int target, vector<int> &candidates,
               vector<int> &current, vector<vector<int>> &ans) {
    if(target == 0) {
        ans.push_back(current);
        return;
    }

    for(int i = start; i < candidates.size(); i++) {
        // If the candidate exceeds the remaining target, stop if sorted, or skip
        if(candidates[i] > target)
            continue;

        current.push_back(candidates[i]);
        // Re-use current element: pass 'i', NOT 'i + 1'
        backtrack(i, target - candidates[i], candidates, current, ans);
        current.pop_back(); // Backtrack
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> ans;
    vector<int> current;

    // Sorting is optional, but helps prune early (candidates[i] > target)
    sort(candidates.begin(), candidates.end());

    backtrack(0, target, candidates, current, ans);
    return ans;
}

// Approach 1: Using Include/Exclude Pattern
void findCombinations(int index, int target, vector<int> &candidates,
                      vector<int> &current, vector<vector<int>> &ans) {
    // Base Case 1: Target reached!
    if(target == 0) {
        ans.push_back(current);
        return;
    }

    // Base Case 2: Out of bounds or target exceeded
    if(index >= candidates.size() || target < 0) {
        return;
    }

    // CHOICE 1: INCLUDE candidates[index] (Stay at 'index' for re-use)
    if(candidates[index] <= target) {
        current.push_back(candidates[index]);
        // Notice: passing 'index', NOT 'index + 1'
        findCombinations(index, target - candidates[index], candidates, current, ans);
        current.pop_back(); // Backtrack
    }

    // CHOICE 2: EXCLUDE candidates[index] (Move forward, never use candidates[index] again)
    findCombinations(index + 1, target, candidates, current, ans);
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> ans;
    vector<int> current;
    findCombinations(0, target, candidates, current, ans);
    return ans;
}
