#include <bits/stdc++.h>
using namespace std;

// N Meetings In One Room
// Pattern: Activity Selection Problem.

// Time: O(N log N)
// Space: O(N)

bool comparator(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int maxMeetings(vector<int> &start, vector<int> &end, int n) {
    vector<pair<int, int>> v;

    for(int i = 0; i < n; i++) {
        pair<int, int> p = make_pair(start[i], end[i]);
        v.push_back(p);
    }

    sort(v.begin(), v.end(), comparator);

    for(const auto p: v)
        cout << p.first << " - " << p.second << endl;

    int count = 1;
    int ansEnd = v[0].second;

    for(int i = 1; i < n; i++) {
        if(v[i].first > ansEnd) {
            count++;
            ansEnd = v[i].second;
        }
    }

    return count;
}

int main() {
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end = {2, 4, 6, 7, 9, 9};

    int n = 6;

    cout << maxMeetings(start, end, n) << endl;

    return 0;
}