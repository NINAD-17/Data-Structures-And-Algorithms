#include <bits/stdc++.h>
using namespace std;

void debugPrint(vector<int> &v) {
    cout << "[";
    for(int i: v)
        cout << i << " ";
    cout << "]  ";
}

// Time: O(n^2)
// Space: O(1)
int numSubarrayProductLessThanK(vector<int> &nums, int k) {
    if(k <= 1) return 0;
    int count = 0;
    int n = nums.size();

    for(int i = 0; i < n; i++) {
        long long product = 1;
        vector<int> v;
        
        for(int j = i; j < n; j++) {
            product *= nums[j];
            v.push_back(nums[j]);

            if(product < k) {
                count++;
                debugPrint(v);
            } else {
                break;
            }
        }
    }

    return count;
}

int main() {
    vector<int> nums = {10, 5, 2, 6};
    int k = 100;

    cout << endl << numSubarrayProductLessThanK(nums, k) << endl;
    return 0;
}