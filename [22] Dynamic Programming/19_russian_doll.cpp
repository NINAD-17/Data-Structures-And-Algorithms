#include <bits/stdc++.h>
using namespace std;

// Russian Doll Envelopes
// You're given 2D array of integers `envelope` where envelopes[i] = [wi, hi] represent width and height of envelope.
// One envelope can fit into other only if both the width and height of one envelope are greater than other's. 
// Return max number of envelopes you can Russian Doll (i.e. put one inside the other).

// Time Complexity:  O(N log N)  [Sorting O(N log N) + LIS Binary Search O(N log N)]
// Space Complexity: O(N)        [For the LIS tails array]

// Custom comparator:
// 1. Sort by width ASCENDING
// 2. If widths are equal, sort by height DESCENDING (prevents nesting same-width envelopes)
static bool compareEnvelopes(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0]) {
        return a[1] > b[1]; // Height descending on tie
    }
    return a[0] < b[0];     // Width ascending
}

int maxEnvelopes(vector<vector<int>> &envelopes) {
    int n = envelopes.size();
    if (n == 0)
        return 0;

    // Step 1: Sort envelopes
    sort(envelopes.begin(), envelopes.end(), compareEnvelopes);

    // Step 2: Run 1D LIS (Binary Search) on heights
    vector<int> ans;
    ans.push_back(envelopes[0][1]);

    for (int i = 1; i < n; i++) {
        int currHeight = envelopes[i][1];

        if (currHeight > ans.back()) {
            ans.push_back(currHeight);
        } else {
            // Find index of first height >= currHeight
            int index = lower_bound(ans.begin(), ans.end(), currHeight) - ans.begin();
            ans[index] = currHeight;
        }
    }

    return ans.size();
}

int main() {
    vector<vector<int>> envelopes1 = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    vector<vector<int>> envelopes2 = {{1, 1}, {1, 1}, {1, 1}};

    cout << "Example 1 Max Envelopes: " << maxEnvelopes(envelopes1) << endl; // Expected: 3
    cout << "Example 2 Max Envelopes: " << maxEnvelopes(envelopes2) << endl; // Expected: 1

    return 0;
}