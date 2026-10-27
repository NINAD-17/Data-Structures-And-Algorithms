#include <bits/stdc++.h>
using namespace std;

// Time: O(n log n)
// Space: O(n)
void wiggleSort(vector<int> &nums) {
    int n = nums.size();

    // 1. Create a sorted copy
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());

    // mid points to the end of the smaller half
    // (n + 1) / 2 ensures smaller half gets the extra element if n is odd
    int left = (n - 1) / 2;
    int right = n - 1; // right points to the end of the larger half

    // 2. Distribute into original array
    // Fill odd positions first with the larger half (descending)
    for(int i = 1; i < n; i += 2) {
        nums[i] = sorted[right--];
    }

    // Fill even positions with the smaller half (descending)
    for(int i = 0; i < n; i += 2) {
        nums[i] = sorted[left--];
    }
}

void wiggleSortII(vector<int> &nums) {
    vector<int> v = nums;
    sort(v.begin(), v.end());

    int j = (v.size() - 1) / 2;
    int k = v.size() - 1;

    for(int i = 0; i < nums.size(); i++) {
        if(i % 2 == 0) {
            nums[i] = v[j];
            j--;
        } else {
            nums[i] = v[k];
            k--;
        }
    }
}