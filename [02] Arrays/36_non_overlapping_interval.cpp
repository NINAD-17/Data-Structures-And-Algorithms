#include <bits/stdc++.h>
using namespace std;

// Non-overlapping Interval:
// https://leetcode.com/problems/non-overlapping-intervals/

// Greedy Rule
// When two intervals overlap, you must delete the one that ends later. 
// Why? Because an interval that extends far into the future has a much higher chance of colliding with subsequent intervals. 
//      By greedily keeping the one with the smaller end value ($\min(\text{end}_1, \text{end}_2)$), you leave the maximum possible room for upcoming intervals.

// My Solution
// Time: O(n log n)
// Space: O(log n)
int eraseOverlapIntervals(vector<vector<int>> &intervals) {
    if(intervals.empty())
        return 0;

    // Sort all intervals
    sort(intervals.begin(), intervals.end());

    int count = 0;
    int prevEnd = intervals[0][1]; // Track only end time

    for(int i = 1; i < intervals.size(); i++) {
        vector<int> interval = intervals[i];

        if(interval[0] < prevEnd) {
            // Case 1: Overlap
            count++;

            // Greedily keep the interval that ends earlier
            prevEnd = min(interval[1], prevEnd);
        } else {
            // Case 2: No Overlap
            prevEnd = interval[1];
        }
    }

    return count;
}

int eraseOverlapIntervals_2(vector<vector<int>> &intervals) {
    if(intervals.empty())
        return 0;

    // Sort primarily by end time
    sort(
        intervals.begin(), intervals.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; });

    int count = 0;
    int prevEnd = intervals[0][1];

    for(int i = 1; i < intervals.size(); i++) {
        if(intervals[i][0] < prevEnd) {
            // Must remove intervals[i] because prevEnd is already as small as
            // possible
            count++;
        } else {
            prevEnd = intervals[i][1];
        }
    }

    return count;
}