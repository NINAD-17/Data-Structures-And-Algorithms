#include <bits/stdc++.h>
using namespace std;

// Counting Bits: https://leetcode.com/problems/counting-bits/description/

// Optimal Solution
// Time Complexity: O(n)
// Auxiliary Space (Extra Space): O(1)
vector<int> countBits_dp(int n) {
    // Using 1D DP (Tabulation)

    vector<int> ans(n + 1, 0);

    // ans[0] is 0
    for (int i = 1; i <= n; i++) {
        ans[i] = ans[(i >> 1)] + (i & 1);
    }

    return ans;
}

int countOnes(int num) {
    int count = 0;

    while (num != 0) {
        int bit = num & 1;

        if (bit == 1)
            count++;

        num = num >> 1;
    }

    return count;
}

// Time Complexity: O(n log n)
vector<int> countBits(int n) {
    vector<int> ans(n + 1);

    for (int i = 0; i <= n; i++) {
        ans[i] = countOnes(i);
    }

    return ans;
}

int main() {
    int n = 10;

    vector<int> ans_1 = countBits(n);
    for (auto i : ans_1)
        cout << i << " ";
    cout << endl;

    vector<int> ans_2 = countBits_dp(n);
    for (auto i : ans_2)
        cout << i << " ";
    cout << endl;

    return 0;
}