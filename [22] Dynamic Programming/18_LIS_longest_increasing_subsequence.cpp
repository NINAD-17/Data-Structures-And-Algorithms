#include <bits/stdc++.h>
using namespace std;

// LIS - Longest Increasing Subsequence
// Given an array of integers, find the length of the longest (strictly) increasing subsequence from the given array.

// Example: [5, 8, 3, 7, 9, 1]
// Subsequences: [5, 8, 9], [8, 9], [3, 7, 9], [7, 9], [9], [1]
//      Therefore LIS is of size 3.

// Optimal Approach
// Time: O(n log n)
// Space: O(n)
int usingBinarySearch(vector<int> &arr, int n) {
    if(n == 0)
        return 0;

    vector<int> ans;
    ans.push_back(arr[0]);

    for(int i = 1; i < n; i++) {
        if(arr[i] > ans.back()) {
            ans.push_back(arr[i]);
        } else {
            // find index of just big element in ans
            int index = lower_bound(ans.begin(), ans.end(), arr[i]) - ans.begin();
            ans[index] = arr[i];
        }
    }

    return ans.size();
}

// Time: O(n^2)
// Space: O(2 * (n + 1)) => O(n)
int usingTabulation_SpaceOptimized(vector<int> &arr, int n) {
    vector<int> curr(n + 1, 0); // current row
    vector<int> next(n + 1, 0); // next row

    for(int currIndex = n - 1; currIndex >= 0; currIndex--) {
        for(int prevIndex = currIndex - 1; prevIndex >= -1; prevIndex--) {
            int include = 0;
            if(prevIndex == -1 || arr[currIndex] > arr[prevIndex])
                include = 1 + next[currIndex + 1];

            // Exclude
            int exclude = 0 + next[prevIndex + 1];

            curr[prevIndex + 1] = max(include, exclude);
        }
        
        next = curr;
    }

    return next[0];
}

// Time: O(n^2)
// Space: O(n^2)
int usingTabulation(vector<int> &arr, int n) {
    vector<vector<int>> dp(n + 1, vector<int> (n + 1, 0));

    for(int currIndex = n - 1; currIndex >= 0; currIndex--) {
        for(int prevIndex = currIndex - 1; prevIndex >= -1; prevIndex--) {
            int include = 0;
            if(prevIndex == -1 || arr[currIndex] > arr[prevIndex])
                include = 1 + dp[currIndex + 1][currIndex + 1];

            // Exclude
            int exclude = 0 + dp[currIndex + 1][prevIndex + 1];

            dp[currIndex][prevIndex + 1] = max(include, exclude);
        }
    }

    return dp[0][-1 + 1]; // i.e. dp[0][0]
}

// Time: O(n^2)
// Space: O(n^2)
int usingMemoization(vector<int> &arr, int n, int currIndex, int prevIndex, vector<vector<int>> &dp) {
    // Base Case
    if(currIndex == n) 
        return 0;

    if(dp[currIndex][prevIndex + 1] != -1)
        return dp[currIndex][prevIndex + 1];

    // Include
    int include = 0;
    if(prevIndex == -1 || arr[currIndex] > arr[prevIndex])
        include = 1 + usingMemoization(arr, n, currIndex + 1, currIndex, dp);

    // Exclude
    int exclude = 0 + usingMemoization(arr, n, currIndex + 1, prevIndex, dp);

    dp[currIndex][prevIndex + 1] = max(include, exclude);
}

int usingRecursion(vector<int> &arr, int n, int currIndex, int prevIndex) {
    // Base Case
    if(currIndex == n) 
        return 0;

    // Include
    int include = 0;
    if(prevIndex == -1 || arr[currIndex] > arr[prevIndex])
        include = 1 + usingRecursion(arr, n, currIndex + 1, currIndex);

    // Exclude
    int exclude = 0 + usingRecursion(arr, n, currIndex + 1, prevIndex);

    return max(include, exclude);
}

void usingRecursion_subsequence_print(vector<int> &arr, int n, int currIndex, int prevIndex, vector<int> &currSeq, vector<int> &bestSeq) {
    // Base Case
    if(currIndex == n) {
        if(currSeq.size() > bestSeq.size())
            bestSeq = currSeq;
        return ;
    }

    // Include
    if(prevIndex == -1 || arr[currIndex] > arr[prevIndex]) {
        currSeq.push_back(arr[currIndex]);
        usingRecursion_subsequence_print(arr, n, currIndex + 1, currIndex, currSeq, bestSeq);
        currSeq.pop_back(); // backtrack
    }

    // Exclude
    usingRecursion_subsequence_print(arr, n, currIndex + 1, prevIndex, currSeq, bestSeq);
}

int bruteForce_iterative(vector<int> &arr) {
    int maxSubsequenceSize = 0;

    for(int i = 0; i < arr.size(); i++) {
        int currMax = arr[i];
        int currSubsequenceSize = 1;
        
        for(int j = i + 1; j < arr.size(); j++) {
            if(arr[j] > currMax) {
                currSubsequenceSize++;
                currMax = arr[j];
            }
        }

        maxSubsequenceSize = max(currSubsequenceSize, maxSubsequenceSize);
    }

    return maxSubsequenceSize;
}

int longestSubsequence(vector<int> &arr) {
    cout << "Brute Force Approach: " << bruteForce_iterative(arr) << endl;

    cout << "Using Recursion: " << usingRecursion(arr, arr.size(), 0, -1) << endl;

    vector<int> currSeq, bestSeq;
    usingRecursion_subsequence_print(arr, arr.size(), 0, -1, currSeq, bestSeq);
    cout << "LIS length = " << bestSeq.size() << endl;
    cout << "LIS subsequence = ";
    for(int x : bestSeq) cout << x << " ";
    cout << endl;

    vector<vector<int>> dp(arr.size() + 1, vector<int> (arr.size() + 1, -1));
    cout << "Using Memoization: " << usingMemoization(arr, arr.size(), 0, -1, dp) << endl;

    cout << "Using Tabulation: " << usingTabulation(arr, arr.size()) << endl;

    cout << "Using binary search: " << usingBinarySearch(arr, arr.size()) << endl;
}

int main() {
    vector<int> arr = {5, 8, 3, 7, 9, 1};

    longestSubsequence(arr);

    return 0;
}