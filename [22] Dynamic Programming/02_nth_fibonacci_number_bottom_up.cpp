#include <bits/stdc++.h>
using namespace std;

// Method: Bottom Up (Tabulation)

// Time Complexity: O(n)
// Space Complexity: O(1)
void fib_bottom_up_space_optimized(int n) {
    int prev1 = 1;
    int prev2 = 0;

    for(int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    cout << prev1 << endl;
}


// Time Complexity: O(n)
// Space Complexity: O(n)
void fib_bottom_up(int n) {
    // Create DP Array
    vector<int> dp(n + 1);

    // Set DP of 0 and 1 (Same as Base Case)
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    cout << dp[n] << endl;
}

int main() {
    int n = 6;
    // cin >> n;

    fib_bottom_up(n);
    return 0;
}