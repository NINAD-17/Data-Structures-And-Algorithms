#include <bits/stdc++.h>
using namespace std;

// Merge Intervals: https://leetcode.com/problems/merge-intervals/

// Time: O(n log n)
// Space: O(log n) used by sort()
vector<vector<int>> merge(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> merged;

    for(int i = 0; i < intervals.size(); i++) {
        // If merged is empty OR there's no overlap with prev interval
        if(merged.empty() || merged.back()[1] < intervals[i][0]) {
            merged.push_back(intervals[i]);
        } else {
            // There's an overalp
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        }
    }

    return merged;
}

// Brute Force
// Time: O(n^2)
// Space: O(log n)
vector<vector<int>> merge(vector<vector<int>> &intervals) {
    int n = intervals.size();
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;

    for(int i = 0; i < n; i++) {
        int start = intervals[i][0];
        int end = intervals[i][1];

        // If the current interval is already covered by the last merged
        // interval, skip it
        if(!ans.empty() && end <= ans.back()[1]) {
            continue;
        }

        // Look ahead to check all possible overlapping intervals
        for(int j = i + 1; j < n; j++) {
            if(intervals[j][0] <= end) {
                end = max(end, intervals[j][1]);
            } else {
                break; // No further intervals can overlap because the array is
                       // sorted
            }
        }

        ans.push_back({start, end});
    }

    return ans;
}

int main() {
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    vector<vector<int>> merged = merge(intervals);
    for(auto interval : merged) {
        for(auto val : interval)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}