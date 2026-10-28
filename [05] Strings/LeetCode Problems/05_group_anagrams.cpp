#include <bits/stdc++.h>
using namespace std;

// Optimal - O(N.K)
vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> groups;

    for(int i = 0; i < strs.size(); i++) {
        // Step 1: Count frequency of each letter 'a' through 'z'
        vector<int> count(26, 0);
        for(char ch : strs[i])
            count[ch - 'a']++;

        // Step 2: Build a unique signature string, e.g. "#1#0#0#0#1..."
        string signature = "";
        for(int c = 0; c < 26; c++)
            signature += '#' + to_string(count[c]);

        // Step 3: Insert original string into its signature group
        groups[signature].push_back(strs[i]);
    }

    // Step 4: Collect all groups into the final result
    vector<vector<string>> result;
    for(auto entry : groups)
        result.push_back(entry.second);

    return result;
}

// Optimal - O(N . K log k)
vector<vector<string>> groupAnagrams_2(vector<string> &strs) {
    int n = strs.size();

    if(n == 1)
        return {{strs[0]}};

    unordered_map<string, vector<string>> anagramGroups;

    for(const string &word : strs) {
        string sortedKey = word;
        sort(sortedKey.begin(), sortedKey.end());
        anagramGroups[sortedKey].push_back(word);
    }

    vector<vector<string>> result;
    result.reserve(anagramGroups.size());

    for(auto entry : anagramGroups) {
        result.push_back(entry.second);
    }

    return result;
}

// Brute Force
// Time: O(N^2 . K)
// Space: O(n)

bool areAnagrams(const string &a, const string &b) {
    if(a.length() != b.length())
        return false;

    vector<int> freq(26, 0);
    for(char ch : a)
        freq[ch - 'a']++;
    for(char ch : b)
        freq[ch - 'a']--;

    for(int count : freq)
        if(count != 0)
            return false;

    return true;
}

vector<vector<string>> groupAnagramsBruteForce(vector<string> &strs) {
    int n = strs.size();
    vector<bool> visited(n, false);
    vector<vector<string>> result;

    for(int i = 0; i < n; i++) {
        if(visited[i])
            continue;

        vector<string> group;
        group.push_back(strs[i]);
        visited[i] = true;

        for(int j = i + 1; j < n; j++) {
            if(!visited[j] && areAnagrams(strs[i], strs[j])) {
                group.push_back(strs[j]);
                visited[j] = true;
            }
        }

        result.push_back(group);
    }

    return result;
}