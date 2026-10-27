#include <bits/stdc++.h>
using namespace std;

// Brute Force
vector<int> countSmaller(vector<int> &nums) {
    int n = nums.size();
    vector<int> count(n, 0);

    for(int i = 0; i < nums.size(); i++) {
        int smallerElem = 0;
        for(int j = i + 1; j < nums.size(); j++) {
            if(nums[j] < nums[i])
                smallerElem++;
        }
        count[i] = smallerElem;
    }

    return count;
}