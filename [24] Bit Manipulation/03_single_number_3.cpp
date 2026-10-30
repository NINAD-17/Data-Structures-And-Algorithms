#include <bits/stdc++.h>
using namespace std;

// Single Number III: https://leetcode.com/problems/single-number-iii/

// Optimal Solution
// Time Complexity: O(n)
// Auxiliary Space (Extra Space): O(1)
vector<int> singleNumber_optimized(vector<int> &nums) {
    // Step 1: XOR all numbers
    long long xorAll = 0;
    for (auto num : nums)
        xorAll ^= num;

    // Step 2: Find rightmost set bit
    long long rightmostBit = xorAll & (-xorAll);

    // Step 3: Divide into two groups and XOR separately
    int num1 = 0;
    int num2 = 0;

    for (auto num : nums) {
        if (num & rightmostBit) {
            num1 ^= num; // Group 1
        } else {
            num2 ^= num; // Group 2
        }
    }

    return {num1, num2};
}

// Time Complexity: O(n)
// Auxillary Space: O(n)
vector<int> singleNumber(vector<int> &nums) {
    unordered_map<int, int> freq;
    vector<int> ans;

    for (int i = 0; i < nums.size(); i++) {
        freq[nums[i]]++;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (freq.count(nums[i]) && freq[nums[i]] == 1)
            ans.push_back(nums[i]);
    }

    return ans;
}

int main() {
    vector<int> nums = {1, 2, 1, 3, 2, 5};

    vector<int> ans_1 = singleNumber(nums);
    for (auto i : ans_1)
        cout << i << " ";
    cout << endl;

    vector<int> ans_2 = singleNumber_optimized(nums);
    for (auto i : ans_2)
        cout << i << " ";
    cout << endl;

    return 0;
}