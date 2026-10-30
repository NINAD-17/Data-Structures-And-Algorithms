#include <bits/stdc++.h>
using namespace std;

// Single Number II: https://leetcode.com/problems/single-number-ii/

// Optimal Solution
// Time Complexity: O(n)
// Auxiliary Space (Extra Space): O(1)
int singleNumber_optimized(vector<int> &nums) {
    int result = 0;

    // Iterate through all 32 bit positions
    for (int bitIndex = 0; bitIndex < 32; bitIndex++) {
        int bitCount = 0;

        // Count how many numbers have bitIndex set
        for (int num : nums) {
            if ((num >> bitIndex) & 1)
                bitCount++;
        }

        // If bitCount % 3 == 1, unique number has this bit set
        if (bitCount % 3 == 1) {
            result |= (1U << bitIndex);
        }
    }

    return result;
}

// Time Complexity: O(n log n)
// Auxillary Space: O(1)
int singleNumber(vector<int> &nums) {
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 1; i += 3) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }

    return nums[nums.size() - 1]; // OR return nums.back();
}

int main() {
    vector<int> nums = {2, 2, 3, 2};

    int ans_1 = singleNumber(nums);
    cout << ans_1 << endl;

    int ans_2 = singleNumber_optimized(nums);
    cout << ans_2 << endl;

    return 0;
}