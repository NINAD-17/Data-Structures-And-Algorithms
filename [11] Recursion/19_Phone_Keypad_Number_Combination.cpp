#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define KEYPAD {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}

// --- Recursive Apporach ---
// Time Complexity: O(N * 4^N)
// Auxillary Space Complexity: O(N)
//      - Total (including ans) it's O(N * 4^N)
void generateCombinations(string &inputNo, string &output, int index, vector<string> &ans) {
    // Base Case
    if(index >= inputNo.size()) {
        ans.push_back(output);
        return ;
    }

    if (inputNo.empty()) return ;

    // Keypad
    string keypad[] = KEYPAD;
    
    int number = inputNo[index] - '0'; // to get a number and not char. // Ex - ASCII of char '2' is 50 and char '0' is 48 so 50 - 48 = 2 and we get 2 in numbers.
    string keypadStr = keypad[number];

    for(int i = 0; i < keypadStr.length(); i++) {
        output.push_back(keypadStr[i]);
        generateCombinations(inputNo, output, index + 1, ans);
        output.pop_back();
    }
}

vector<string> letterCombinations(string &inputNo) {
    vector<string> ans;
    string output;
    int index = 0;

    generateCombinations(inputNo, output, index, ans);
    return ans;
}

// --- iterative approach using queue ---
vector<string> letterCombinations_iterative(string &inputNo) {
    if(inputNo.empty())
        return {};
    
    const string mapping[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    queue<string> q;
    q.push("");

    while(!q.empty()) {
        string str = q.front();
        q.pop();

        if(str.length() == inputNo.length()) { // if the str from queue has length equal to length of input number ("23" means length is 2) then add it to the answer
            ans.push_back(str);
        } else {
            int digit = inputNo[str.length()] - '0';
            string letters = mapping[digit];
            for(int i = 0; i < letters.length(); i++) {
                q.push(str + letters[i]); // remember that we're not doing str += letters[i] means we're adding str + letters[i] in queue and not modifying str
            }
        }
    }

    return ans;
}

int main() {
    string inputNo = "234";

    vector<string> ans = letterCombinations(inputNo);
    // vector<string> ans = letterCombinations_iterative(inputNo);
    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] << endl;
    
    return 0;
}