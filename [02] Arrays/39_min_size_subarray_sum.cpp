#include <bits/stdc++.h>
using namespace std;

// Minimum Size Subarray Sum:
// https://leetcode.com/problems/minimum-size-subarray-sum/description/

// Optimal - Sliding Window Approach
// Time Complexity: O(n) — Both left and right traverse the array at most once (at most 2n total pointer moves).
// Space Complexity: O(1) — Only simple integer variables used.
int minSubArrayLen(int target, vector<int> &nums) {
    int wStart = 0;
    int currSum = 0;
    int minLen = INT_MAX;

    // Outer loop expands the window using wEnd
    for(int wEnd = 0; wEnd < nums.size(); wEnd++) {
        currSum += nums[wEnd]; // Add incoming element once

        // Inner loop shrinks the window using wStart while condition is
        // satisfied
        while(currSum >= target) {
            int len = wEnd - wStart + 1;
            minLen = min(minLen, len);

            currSum -= nums[wStart]; // Remove outgoing element
            wStart++;                // Advance start
        }
    }

    return (minLen == INT_MAX) ? 0 : minLen;
}

// Brute Force
// Time: O(n^2)
// Space: O(1)
int minSubArrayLen_2(int target, vector<int> &nums) {
    int size = nums.size();
    int minLen = INT_MAX;

    for(int i = 0; i < size; i++) {
        int currSum = 0;

        for(int j = i; j < size; j++) {
            currSum += nums[j];

            if(currSum >= target) {
                int len = (j - i) + 1;
                minLen = min(minLen, len);
                break; // Any longer subarray starting at i will only be larger,
                       // so stop early!
            }
        }
    }

    // If no valid subarray - return 0
    return (minLen == INT_MAX) ? 0 : minLen;
}