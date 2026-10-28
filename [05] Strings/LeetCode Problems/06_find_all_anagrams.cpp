#include <bits/stdc++.h>
using namespace std;

// Leetcode: https://leetcode.com/problems/find-all-anagrams-in-a-string/

// Time: O(N)
// Space: O(1)
vector<int> findAnagrams(string s, string p) {
    int sLen = s.length();
    int pLen = p.length();

    if(pLen > sLen)
        return {};

    vector<int> result;
    vector<int> pFreq(26, 0);
    vector<int> sFreq(26, 0);

    for(int i = 0; i < pLen; i++) {
        pFreq[p[i] - 'a']++;
        sFreq[s[i] - 'a']++; // for first window
    }

    // intial window check
    if(sFreq == pFreq)
        result.push_back(0);

    for(int i = pLen; i < sLen; i++) {
        sFreq[s[i] - 'a']++; // incoming right char

        sFreq[s[i - pLen] - 'a']--; // oldest outgoing left char

        if(sFreq == pFreq)
            result.push_back(i - pLen + 1);
    }

    return result;
}

int main() {
    string s = "cbaebabacd", p = "abc";

    vector<int> ans = findAnagrams(s, p);

    for(int i: ans)
        cout << i << " ";
    
    return 0;
}