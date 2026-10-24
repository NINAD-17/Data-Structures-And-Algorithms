#include <iostream>
#include <vector>
using namespace std;

// Leetcode: https://leetcode.com/problems/generate-parentheses/description/

// 1. Backtracking Approach (preferred)
// Time: O(c(n) * n)
// Auxillary Space: O(n)
// Output Space: O(c(n) * n)
// Refer README.md for complexity analysis.

// Helper function that explores all choices
void solve(int open, int close, int n, string &current, vector<string> &ans) {

    // BASE CASE:
    // We have used all n open and all n close brackets.
    // Total characters added = 2 * n.
    if(current.length() == 2 * n) {
        ans.push_back(current); // Save this valid combination
        return;
    }

    // CHOICE 1: Try placing an opening bracket '('
    if(open < n) {
        current.push_back('(');                  // 1. DO: place '('
        solve(open + 1, close, n, current, ans); // 2. RECURSE: go deeper
        current.pop_back();                      // 3. UNDO (Backtrack): remove '(' so other branches can try
    }

    // CHOICE 2: Try placing a closing bracket ')'
    if(close < open) {
        current.push_back(')');                  // 1. DO: place ')'
        solve(open, close + 1, n, current, ans); // 2. RECURSE: go deeper
        current.pop_back();                      // 3. UNDO (Backtrack): remove ')'
    }
}

vector<string> generateParentheses(int n) {
    vector<string> ans;
    string current = "";

    // Start recursion with 0 open brackets and 0 close brackets used
    solve(0, 0, n, current, ans);

    return ans;
}


// 2. DP Approach
vector<string> generateParenthesis(int n) {
    // dp[i] stores all valid parentheses strings formed using 'i' pairs
    vector<vector<string>> dp(n + 1);

    // Base case: 0 pairs has 1 valid string: the empty string ""
    dp[0] = {""};

    // Build up from 1 pair up to n pairs
    for(int i = 1; i <= n; i++) {
        // j represents the number of pairs placed inside the first '(' and ')'
        for(int j = 0; j < i; j++) {
            // Number of pairs placed outside is (i - 1 - j)
            const vector<string> &insideList = dp[j];
            const vector<string> &outsideList = dp[i - 1 - j];

            // Cartesian product: combine every inside choice with every outside choice
            for(const string &inside : insideList) {
                for(const string &outside : outsideList) {
                    dp[i].push_back("(" + inside + ")" + outside);
                }
            }
        }
    }

    return dp[n];
}

int main() {
    int n = 2;

    vector<string> parentheses = generateParentheses(n);
    for(auto &p : parentheses)
        cout << p << " ";
    cout << endl;

    return 0;
}