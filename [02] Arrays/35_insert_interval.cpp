#include <bits/stdc++.h>
using namespace std;

// Insert Interval: https://leetcode.com/problems/insert-interval/description/

// My Solution
// Time: O(n)
// Space: O(1)
vector<vector<int>> insert(vector<vector<int>> &intervals,
                           vector<int> &newInterval) {
    vector<vector<int>> ans;
    bool isInserted = false;

    for(int i = 0; i < intervals.size(); i++) {
        vector<int> interval = intervals[i];

        if(isInserted) {
            // Case 0: newInterval already inserted - push all remaining
            // intervals
            ans.push_back(interval);
        } else if(newInterval[1] < interval[0]) {
            // Case 1: newInterval is strictly before the current interval
            ans.push_back(newInterval);
            ans.push_back(interval);
            isInserted = true;
        } else if(interval[1] < newInterval[0]) {
            // Case 2: interval is strictly before the current interval
            ans.push_back(interval);
        } else {
            // Case 3: Overlap -> expand newInterval
            newInterval[0] = min(interval[0], newInterval[0]);
            newInterval[1] = max(interval[1], newInterval[1]);
        }
    }

    if(!isInserted) {
        // If newInterval was never inserted - push it to the end
        ans.push_back(newInterval);
    }

    return ans;
}

// Using while loops
// Time: O(n)
// Space: O(1)
vector<vector<int>> insert(vector<vector<int>> &intervals,
                           vector<int> &newInterval) {
    vector<vector<int>> ans;
    int i = 0;
    int n = intervals.size();

    // Phase 1: Add all intervals that finish before newInterval starts
    while(i < n && intervals[i][1] < newInterval[0]) {
        ans.push_back(intervals[i]);
        i++;
    }

    // Phase 2: Merge all overlapping intervals with newInterval
    while(i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    // Insert the merged newInterval
    ans.push_back(newInterval);

    // Phase 3: Add all remaining intervals that start after newInterval ends
    while(i < n) {
        ans.push_back(intervals[i]);
        i++;
    }

    return ans;
}