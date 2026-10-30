#include <bits/stdc++.h>
using namespace std;

// Leetcode: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/

// Mental Shift between approaches:
// 1. DSU/Array - "For this event, what is the earliest free day I can book?" (Iterating through events).
// 2. Priority Queue - "For this current day, which available event should I attend?" (Simulating day-by-day).

// Approach 3: Priority Queue (Optimal)
// Time: O(N log N)
// Space: O(N)
int maxEvents(vector<vector<int>> &events) {
    // Sort events primarily by their start day
    sort(events.begin(), events.end());

    // Min-heap to store the endDay of currently open events
    priority_queue<int, vector<int>, greater<int>> minHeap;

    int totalEvents = events.size();
    int eventIdx = 0;
    int maxAttended = 0;
    int day = 0;

    // Run day by day while there are events to process or in the heap
    while(eventIdx < totalEvents || !minHeap.empty()) {
        // Fast-forward day if no events are currently active in heap
        if(minHeap.empty()) {
            day = events[eventIdx][0];
        }

        // 1. Push all events starting on or before 'day'
        while(eventIdx < totalEvents && events[eventIdx][0] <= day) {
            minHeap.push(events[eventIdx][1]);
            eventIdx++;
        }

        // 2. Remove all events that have already expired
        while(!minHeap.empty() && minHeap.top() < day) {
            minHeap.pop();
        }

        // 3. Greedily attend the event that expires earliest
        if(!minHeap.empty()) {
            minHeap.pop();
            maxAttended++;
            day++; // Used up this day
        }
    }

    return maxAttended;
}

// Approach 2: Disjoint Set Union (DSU/ Union Find) (Path Compression)
// We'll use approach 1 with an optimization:
//      When days $1, 2, 3, \dots, 5000$ are already booked, the next event starting at Day 1 has to linearly check 5000 cells just to find that Day 5001 is the first free slot.
//      If you could jump directly from Day 1 to Day 5001 in $O(1)$ or nearly constant time, the inner loop vanishes!
// Disjoint Set Union (Path Compression)
int findParent(int d, vector<int> &parent) {
    if(parent[d] == d)
        return d;
    return parent[d] = findParent(parent[d], parent); // Path compression: jumps straight to the answer
}

// Time: O(N log N) alpha D
// Space: O(D)
int maxEventsDSU(vector<vector<int>> &events) {
    // 1. Sort by endDay ascending
    sort(events.begin(), events.end(), [](const vector<int> &a, const vector<int> &b) {
        if(a[1] == b[1])
            return a[0] < b[0];
        return a[1] < b[1];
    });

    int maxDay = 0;
    for(const auto &e : events) {
        maxDay = max(maxDay, e[1]);
    }

    // parent array where parent[i] points to the next free day >= i
    // size is maxDay + 2 to safely point to (maxDay + 1) when maxDay is taken
    vector<int> parent(maxDay + 2);
    for(int i = 1; i <= maxDay + 1; i++) {
        parent[i] = i;
    }

    int attended = 0;

    for(const auto &e : events) {
        int start = e[0];
        int end = e[1];

        // Jump straight to the earliest unbooked day >= start in O(1)
        int freeDay = findParent(start, parent);

        // If this free day is within the event's valid window
        if(freeDay <= end) {
            attended++;
            // Book this day: point it to the next day's free slot
            parent[freeDay] = findParent(freeDay + 1, parent);
        }
    }

    return attended;
}

// Approach 1: Brute Force Greedy Approach (it gives TLE)
// Time: O(N log N + N * D)
// Space: O(D) ... D stands for Day
int maxEvents(vector<vector<int>> &events) {
    // 1. Sort events by endDay ascending (if equal, startDay ascending)
    sort(events.begin(), events.end(), [](const vector<int> &a, const vector<int> &b) {
        if(a[1] == b[1])
            return a[0] < b[0];
        return a[1] < b[1];
    });

    // 2. Find the maximum day needed
    int maxDay = 0;
    for(const auto &e : events) {
        maxDay = max(maxDay, e[1]);
    }

    // 3. Boolean array to track booked days (1-indexed)
    vector<bool> booked(maxDay + 1, false);
    int attendedCount = 0;

    // 4. For each event, find the earliest free day
    for(const auto &e : events) {
        int start = e[0];
        int end = e[1];

        for(int day = start; day <= end; day++) {
            if(!booked[day]) {
                booked[day] = true;
                attendedCount++;
                break; // Move to the next event
            }
        }
    }

    return attendedCount;
}

int main() {
    vector<vector<int>> events = {{1, 2}, {2, 3}, {3, 4}, {1, 2}};

    cout << maxEvents(events) << endl;

    return 0;
}