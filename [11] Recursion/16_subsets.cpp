#include <iostream>
#include <vector>
using namespace std;

// Leetcode: https://leetcode.com/problems/subsets/description/
// subset always contains 2^n elements. n is the total number of elements in an array.

// Using Backtracking
// Time: O(n * 2^n)
// Space: O(n)
void solve_backtrack(int *arr, int size, vector<int> &output, int index, vector<vector<int>> &ans) {
    // Base Case
    if(index >= size) {
        ans.push_back(output);
        return;
    }

    // Exclude
    solve_backtrack(arr, size, output, index + 1, ans);

    // Include
    int element = arr[index];
    output.push_back(element);
    solve_backtrack(arr, size, output, index + 1, ans);
    output.pop_back(); // backtrack
}

// --- recursion (output vector is passed by value)---
// Time: Total subsets = 2^n. For each subset, building the output vector can take up to O(n) in the worst case.
//       - therefore, O(n * 2^n)
// Space: Recursion depth = O(n). Each recursive call has its own copy of output (since you pass by value).
//       - therefore, O(n * 2^n)
void solve(int *arr, int size, vector<int> output, int index, vector<vector<int>> &ans) {
    // Base Case
    if(index >= size) {
        ans.push_back(output);
        return;
    }

    // Exclude
    solve(arr, size, output, index + 1, ans);

    // Include
    int element = arr[index];
    output.push_back(element);
    solve(arr, size, output, index + 1, ans);
}

vector<vector<int>> subsets(int *arr, int size) {
    vector<vector<int>> ans; // To store all subsets in an array
    vector<int> output; // To store output
    int index = 0;

    solve(arr, size, output, index, ans);
    return ans;
}

// --- Bit Manipulation ---
// Time complexity: O(n * 2^n)
// Space complexity: O(n * 2^n)     If we exclude `ans` vector then it'll be O(n) only.

// 0 means exclude and 1 means include
vector<vector<int>> findSubsets(int *arr, int size) {
    vector<vector<int>> ans;

    // (1 << size) means pow(2, size) => 2^3 = 8
    for(int i = 0; i < (1 << size); i++) { // 0 to 7 [000, 001, 010, 011, 100, 101, 110, 111]
        vector<int> output;
        for(int j = 0; j < size; j++) {
            if((i & (1 << j)) != 0) { // whenever jth bit is set means 1 we'll include arr[j] else exclude
                output.push_back(arr[j]);
            }
        }
        ans.push_back(output);
    }

    return ans;
}

int main() {

    int arr[3] = { 1, 2, 3 };
    int size = 3;

    // vector<vector<int>> ans = subsets(arr, size);
    vector<vector<int>> ans = findSubsets(arr, size);

    // Output
    for(int i = 0; i < ans.size(); i++) {
        if(ans[i].size() == 0)
            cout << "{}";
        for(int j = 0; j < ans[i].size(); j++)
            cout << "{" << ans[i][j] << "}";
        cout << endl;
    }
    cout << endl;

    return 0;
}