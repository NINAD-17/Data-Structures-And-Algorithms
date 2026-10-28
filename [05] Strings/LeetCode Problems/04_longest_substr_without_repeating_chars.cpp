#include <bits/stdc++.h>
using namespace std;

// Optimal
// Similar to min_window_substr
int lengthOfLongestSubstring_2(string s) {
    vector<int> freq(256, 0);
    int left = 0;
    int maxLen = 0;

    for(int right = 0; right < s.length(); right++) {
        char rightChar = s[right];
        freq[rightChar]++;

        // If rightChar is duplicate, shrink from left until it's unique
        while(freq[rightChar] > 1) {
            char leftChar = s[left];
            freq[leftChar]--;
            left++;
        }

        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

// OR Direct-Jump (Store Last Seen Index)
int lengthOfLongestSubstring(string s) {
    // Stores the last seen index of each ASCII character, initialized to -1
    vector<int> lastSeen(256, -1);
    int left = 0;
    int maxLen = 0;

    for(int right = 0; right < s.length(); right++) {
        char currentChar = s[right];

        // If we have seen this char and its index is inside current window
        if(lastSeen[currentChar] >= left) {
            left = lastSeen[currentChar] + 1; // jump left directly
        }

        lastSeen[currentChar] = right; // update last seen position
        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

// Brute Force:
// Time: O(n^2)
// Space: O(1)
int lengthOfLongestSubstringBrute(string s) {
    int n = s.length();
    int maxLen = 0;
    for(int i = 0; i < n; i++) {
        vector<bool> seen(256, false);
        for(int j = i; j < n; j++) {
            char ch = s[j];
            if(seen[ch]) {
                break; // duplicate found, stop expanding from this i
            }
            seen[ch] = true;
            maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}

int main() {
    string s = "abcabcbb"; 

    cout << lengthOfLongestSubstring_2(s) << endl;

    // Output: 3
    // The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.

    return 0;
}