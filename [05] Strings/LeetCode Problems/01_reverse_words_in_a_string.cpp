#include <bits/stdc++.h>
using namespace std;

// Using Two Pointers
// time: O(n)
// space: O(1)
string reverseWords_2(string s) {
    // Step 1: Clean spaces using two pointers
    int write = 0;
    int n = s.length();

    for(int read = 0; read < n; read++) {
        if(s[read] != ' ') {
            if(write != 0) {
                s[write++] = ' '; // space between words
            }

            while(read < n && s[read] != ' ') {
                s[write++] = s[read++];
            }
        }
    }

    s.resize(write); // trim string

    // Step 2: Reverse the whole string
    reverse(s.begin(), s.end());

    // Step 3: Reverse each word
    int start = 0;
    for(int end = 0; end <= s.length(); end++) {
        if(end == s.length() || s[end] == ' ') {
            reverse(s.begin() + start, s.begin() + end);
            start = end + 1;
        }
    }

    return s;
}

// My approach
// time: O(n)
// Space: O(n) // If the input is "a b c d e f", your vector stores 6 strings of 1 character each. The total characters stored across all elements in words is $\approx N$
string reverseWords(string s) {
    vector<string> words;

    string temp = "";

    for(int i = 0; i < s.length(); i++) {
        if(temp.empty() && s[i] == ' ') {
            continue;
        }

        if(!temp.empty() && s[i] == ' ') {
            words.push_back(temp);
            temp = "";
            continue;
        }

        temp += s[i];
    }

    if(!temp.empty())
        words.push_back(temp);

    temp = "";

    for(int i = words.size() - 1; i >= 0; i--) {
        temp += words[i];
        if(i != 0)
            temp += ' ';
    }

    return temp;
}

int main() {
    string str = "a good  example";

    cout << reverseWords_2(str) << endl;
    
    return 0;
}