#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/minimum-window-substring/description/

// Optimal Solution
// Time: O(n + m)
string minWindow_2(string s, string t) {
    int m = s.length();
    int n = t.length();

    // Edge case: impossible to form window if s is shorter than t
    if(m < n)
        return "";

    // Frequency table for required characters in t
    vector<int> targetFreq(128, 0);
    for(char ch : t) {
        targetFreq[ch]++;
    }

    // Frequency table for characters inside our current sliding window
    vector<int> windowFreq(128, 0);

    int matchedCount = 0;
    int minLen = INT_MAX;
    int startIndex = -1;
    int left = 0;

    // Step 1: Expand right pointer
    for(int right = 0; right < m; right++) {
        char rightChar = s[right];
        windowFreq[rightChar]++;

        // Count this character only if it is needed for string t
        if(targetFreq[rightChar] > 0 && windowFreq[rightChar] <= targetFreq[rightChar]) {
            matchedCount++;
        }

        // Step 2: Contract left pointer while the current window is valid
        while(matchedCount == n) {
            int currentLen = right - left + 1;
            if(currentLen < minLen) {
                minLen = currentLen;
                startIndex = left;
            }

            char leftChar = s[left];
            windowFreq[leftChar]--;

            // If removing leftChar makes our window deficient of a required character
            if(targetFreq[leftChar] > 0 && windowFreq[leftChar] < targetFreq[leftChar]) {
                matchedCount--;
            }

            left++; // Shrink window from the left
        }
    }

    return (startIndex == -1) ? "" : s.substr(startIndex, minLen);
}

// Brute force
// Time: O(n^2)
// Space: O(1) as we've used fixed size vector (128)
string minWindow(string s, string t) {
    int m = s.length();
    int n = t.length();

    if(m < n)
        return "";

    // Use a fixed-size array instead of unordered_map for O(1) direct access
    // Index represents ASCII character (size 128 covers all English letters)
    vector<int> targetFreq(128, 0);
    for(char ch : t) {
        targetFreq[ch]++;
    }

    int minLen = INT_MAX;
    int startIndex = -1;

    // Try every possible starting point i
    for(int i = 0; i < m; i++) {
        vector<int> windowFreq(128, 0);
        int matchedCount = 0;

        // Expand end pointer j
        for(int j = i; j < m; j++) {
            char ch = s[j];
            windowFreq[ch]++;

            // Only count this character if it helps fulfill requirement for t
            if(targetFreq[ch] > 0 && windowFreq[ch] <= targetFreq[ch]) {
                matchedCount++;
            }

            // If all characters of t are satisfied
            if(matchedCount == n) {
                int currLen = j - i + 1;
                if(currLen < minLen) {
                    minLen = currLen;
                    startIndex = i;
                }
                // Optimization: Any further expansion from this 'i' will only be longer
                break;
            }
        }
    }

    return (startIndex == -1) ? "" : s.substr(startIndex, minLen);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    cout << minWindow_2(s, t) << endl;

    return 0;
}