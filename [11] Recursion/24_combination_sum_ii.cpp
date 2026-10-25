#include <algorithm>
#include <vector>
using namespace std;

// Leetcode: https://leetcode.com/problems/combination-sum-ii/description/

void getAllCombinations(vector<int> &candidates, int target, int index, vector<int> &current, vector<vector<int>> &ans) {
    // Base case: target matched exactly
    if(target == 0) {
        ans.push_back(current);
        return;
    }

    for(int i = index; i < candidates.size(); i++) {
        // Pruning 1: candidate exceeds remaining target (requires sorted array)
        if(candidates[i] > target) {
            break;
        }

        // Pruning 2: skip duplicate candidates at the current recursion level
        if(i > index && candidates[i] == candidates[i - 1]) {
            continue;
        }

        // 1. DO
        current.push_back(candidates[i]);

        // 2. RECURSE: pass 'i + 1' so each element index is used at most once
        getAllCombinations(candidates, target - candidates[i], i + 1, current, ans);

        // 3. UNDO (Backtrack)
        current.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<vector<int>> ans;
    vector<int> current;

    // Essential: groups duplicates together and allows target pruning
    sort(candidates.begin(), candidates.end());

    getAllCombinations(candidates, target, 0, current, ans);
    return ans;
}