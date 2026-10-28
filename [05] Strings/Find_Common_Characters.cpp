#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// Leetcode: https://leetcode.com/problems/find-common-characters/description/

// Time: O(N) ... here N is total characters from all words
// Aux. Space: O(1) ... excluding result
vector<string> findCommonCharacters(const vector<string> &words) {
    vector<int> minFreq(26, INT_MAX);
    vector<string> result;

    for (const string &word : words) {
        vector<int> charCount(26, 0);
        for (char ch : word) {
            charCount[ch - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            minFreq[i] = min(minFreq[i], charCount[i]);
        }
    }

    for (int i = 0; i < 26; i++) {
        while (minFreq[i] > 0) {
            result.push_back(string(1, 'a' + i));
            minFreq[i]--;
        }
    }

    return result;
}