#include <bits/stdc++.h>
using namespace std;

// Longest Palindromic Substring: https://leetcode.com/problems/longest-palindromic-substring/

// Optimal Approach:
// Time: O(n^2)
// Expands outward from given left and right bounds.
// Returns the length of the palindrome found.
int expandFromCenter(const string &s, int left, int right) {
    while(left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;
        right++;
    }
    // When loop terminates, s[left] != s[right].
    // Valid palindrome boundaries are (left + 1) to (right - 1).
    // Length = (right - 1) - (left + 1) + 1 = right - left - 1.
    return right - left - 1;
}

string longestPalindrome_2(string s) {
    if(s.empty())
        return "";

    int startIndex = 0;
    int maxLen = 0;

    for(int i = 0; i < s.length(); i++) {
        // Check 1: Odd-length palindrome centered at character i
        int lenOdd = expandFromCenter(s, i, i);

        // Check 2: Even-length palindrome centered between i and i + 1
        int lenEven = expandFromCenter(s, i, i + 1);

        int currentMax = max(lenOdd, lenEven);

        if(currentMax > maxLen) {
            maxLen = currentMax;
            // Calculate the start index from center 'i' and length 'maxLen'
            startIndex = i - (maxLen - 1) / 2;
        }
    }

    return s.substr(startIndex, maxLen);
}
// ---------------------------------------------------------------------

bool isPalindrome(string s, int st, int en) {
    while(st < en) {
        if(s[st] != s[en])
            return false;

        st++, en--;
    }

    return true;
}

// Time: O(N^3)
// Space: O(1)
string longestPalindrome(string s) {
    int n = s.length();
    if(n <= 1)
        return s;

    // longest palindrome start index and max length
    int startidx = 0;
    int maxLen = 1;

    // Loop 1: Pick start index (O(N))
    for(int i = 0; i < n - 1; i++) {

        // Loop 2: Pick end index (O(N))
        for(int j = i + 1; j < n; j++) {

            int currLen = j - i + 1;

            // Loop 3: Validate if s[i...j] is a palindrome (O(N))
            if(currLen > maxLen && isPalindrome(s, i, j)) {
                maxLen = currLen;
                startidx = i;
            }
        }
    }

    return s.substr(startidx, maxLen);
}

int main() {
    string s = "babad";

    cout << longestPalindrome_2(s) << endl;

    return 0;
}