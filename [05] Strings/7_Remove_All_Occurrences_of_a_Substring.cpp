#include <iostream>
using namespace std;

// https://leetcode.com/problems/remove-all-occurrences-of-a-substring/

// Time: O(n * m)
// Space: O(n)
string removeOccurrences(string &s, string &part) {
    string stk = "";
    int m = part.length();

    for(char ch: s) {
        stk.push_back(ch);

        if(stk.length() >= m) {
            if(stk.compare(stk.length() - m, m, part) == 0) {
                for(int i = 0; i < m; i++)
                    stk.pop_back();
            }
        }
    }

    return stk;
}

// Time Complexity: The time complexity of the removeAllSubstrings function is O(n * m), 
// where n is the length of the input string str and m is the length of the substring part.
// This is because, in the worst case, the function needs to search for the substring part in the input string str for each character in str, which takes O(n) time.
// The find function takes O(m) time to search for the substring part in the input string str. The erase function takes O(n) time to remove the substring from the input string.
// Therefore, the overall time complexity of the function is O(n * m)

// Find function returns 1st index of than substring
void removeAllSubstrings(string &str, string part) {
    while(str.length() != 0 && str.find(part) < str.length()) {
        cout << str << endl;
        str.erase(str.find(part), part.length());
    }
}


// Time complexity: O(n * m) here m is for O(lenOfsubstr).
//                  - if m is small (like 3 or 4), this is basically O(n)
//                  - If m can be as big as n, then worst case is O(n²)
// Space complexity: O(n + m)
//                  - temp is a new string of size m. That’s O(m) extra space.
//                  - result grows to at most size n. That’s O(n).
string removeSubstrings(string &str, string &substr) {
    // using sliding window
    int lenOfsubstr = substr.length();
    string temp;
    string result = "";
    
    int i = 0, j = 0;
    while(i < str.length() - lenOfsubstr) {
        temp = str.substr(i, lenOfsubstr); // window of substring // time complexity: O(lenOfsubstr) -> substr(i, lenOfsubstr) creates a new string by copying lenOfsubstr characters starting at position i
        
        // debug:
        cout << temp << endl;

        if(temp == substr) {
            i += lenOfsubstr;
            continue;
        } else {
            result += str[i];
            i++;
        }
    }

    while(i < str.length()) {
        result += str[i++];
    }
    
    str = result;
    return str;
}

int main() {
    string str = "daabcbaabcbc", part = "abc";

    // removeAllSubstrings(str, part);
    // cout << str << endl;

    removeSubstrings(str, part);
    cout << str << endl;
    return 0;
}