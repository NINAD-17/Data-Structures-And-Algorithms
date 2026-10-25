#include <iostream>
#include <vector>
using namespace std;

// Pass By Reference Solution with Backtracking
// With string output
// Time: O(n * 2^n)
// Auxillary Space: O(n) 
//      if include ans then O(n * 2^n)
void generate_2(string &str, string &output, int index, vector<string> &ans) {
    if(index >= str.length()) {
        ans.push_back(output);
        return ;
    }

    // Exclude
    generate_2(str, output, index + 1, ans);

    // Include
    output.push_back(str[index]); // OR output += str[index];
    generate_2(str, output, index + 1, ans);

    // Backtrack
    output.pop_back(); // OR output.resize(output.length() - 1)
}

vector<string> generateSequence(string &str) {
    vector<string> ans;
    string output = "";

    generate_2(str, output, 0, ans);
    return ans;
}


// --- Recursion: Using Pass By Value ---
// Note: Here output is vector<string> because of that it's not string output. On empty case it'll give you empty [] and not ""
// Time: O(n * 2^n)
// Auxillary Space: O(n^2) 
//      if include ans then O(n * 2^n)
void generate(string str, vector<string> output, int index, vector<vector<string>> &ans) {
    // Base Case
    if(index >= str.size()) {
        ans.push_back(output);
        return ;
    }

    // Exclude
    generate(str, output, index + 1, ans);

    // Include
    string temp = "";
    temp += str[index];
    output.push_back(temp);

    generate(str, output, index + 1, ans);
} 

vector<vector<string>> generateSubsequence(string str) {
    vector<vector<string>> ans;
    vector<string> output;
    int index = 0;

    generate(str, output, index, ans);
    return ans;
}

// --- using bit manipulation ---
vector<vector<string>> findSubsequences(string str) {
    vector<vector<string>> ans;
    
    for(int i = 0; i < (1 << (str.length())); i++) {
        string temp = "";
        vector<string> output;
        for(int j = 0; j < str.length(); j++) {
            if(i & (1 << j)) {
                temp += str[j];
            }
        }
        output.push_back(temp);
        ans.push_back(output);
    }

    return ans;
}

int main() {
    string str = "abc";

    // vector<vector<string>> ans = generateSubsequence(str);
    vector<vector<string>> ans = findSubsequences(str);

    // Output
    for(int i = 0; i < ans.size(); i++) {
        if (ans[i].size() == 0)
            cout << "{}";
        for(int j = 0; j < ans[i].size(); j++)
            cout << "{" << ans[i][j] << "}";
        cout << endl;
    }
    
    return 0;
}