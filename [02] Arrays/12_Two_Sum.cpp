#include <iostream>
#include <map>
#include <vector>
using namespace std;

// https://leetcode.com/problems/two-sum/

// Time Complexity: O(n) if array is sorted.
// If we use sort() then it will be O(n log n)
vector<int> two_sum_two_ptr(vector<int> &nums, int target) {
    int st = 0, en = nums.size() - 1;
    vector<int> ans;

    while(st < en) {
        if(nums[st] + nums[en] == target) {
            ans.push_back(st++);
            ans.push_back(en--);
        } else if(nums[st] + nums[en] > target) {
            en--;
        } else {
            st++;
        }
    }

    return ans;
}

// Time complexity: O(n^2)
vector<int> twoSum(vector<int> &nums, int target) {
    vector<int> ans;
    for(int i = 0; i < nums.size() - 1; i++) {
        for(int j = i + 1; j < nums.size(); j++) {
            if((nums[i] + nums[j] == target)) {
                ans.push_back(i);
                ans.push_back(j);
                return ans;
            }
        }
    }
    return ans;
}

int main() {
    vector<int> arr = {0, 2, 7, 9, 11, 15};
    int target = 9;

    vector<int> ans = two_sum_two_ptr(arr, target);
    cout << "[ ";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << "]" << endl;
}