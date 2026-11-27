#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007 // %(10 ^ 9 + 7) output could be very large so mod it

// Time: O(N)
// Space: O(1)
long long int usingTabulation_spaceOptimized(int n) {
    long long prev2 = 0;
    long long prev1 = 1;

    for(int i = 3; i <= n; i++) {
        long long int withoutSwap = prev1 % MOD;
        long long int withSwap = prev2 % MOD;

        long long int sum = (withoutSwap + withSwap) % MOD;
        long long int ans = ((n - 1) * sum) % MOD;
        prev2 = prev1;
        prev1 = ans;
    }

    return prev1;
}

// Time: O(N)
// Space: O(N)
long long int usingTabulation(int n) {
    vector<long long int> dp(n + 1, 0);
    dp[1] = 0;
    dp[2] = 1;

    for(int i = 3; i <= n; i++) {
        long long int withoutSwap = dp[i - 1] % MOD;
        long long int withSwap = dp[i - 2] % MOD;

        long long int sum = (withoutSwap + withSwap) % MOD;
        long long int ans = ((n - 1) * sum) % MOD;
        dp[i] = ans;
    }

    return dp[n];
}

// Time: O(N)
// Space: O(N)
long long int usingMemoization(int n, vector<long long int> &dp) {
    // base case
    if(n == 1) // only one element exists, so no derangement possible
        return 0;
    
    if(n == 2) // only 2 elements exists, so 1 derangement possible
        return 1;

    if(dp[n] != -1)
        return dp[n];

    dp[n] = ((n - 1) % MOD) * ((usingMemoization(n - 1, dp) % MOD) + (usingMemoization(n - 2, dp)) % MOD);

    return dp[n];
}

// Time: O(2^N)
// Space: O(N)
long long int usingRecursion(int n) {
    // Base cases
    if(n == 1) // 1 element cannot be placed anywhere else -> 0 derangements
        return 0;
    
    if(n == 2) // 2 elements can only swap with each other -> 1 derangement
        return 1;

    // | 0 | . | . | . | i | . | . | n |
    // Recurrence: f(n) = (n - 1) * [ f(n - 1) + f(n - 2) ]
    // Element 0 has (n - 1) valid positions (any index 'i' from 1 to n - 1).
    // Once element 0 is placed at index 'i', element 'i' has two mutually exclusive choices:
    //   1. Element 'i' goes to index 0 (direct swap):
    //      Both 0 and 'i' are settled -> (n - 2) elements left to derange -> f(n - 2)
    //   2. Element 'i' does NOT go to index 0:
    //      Index 0 now acts as the forbidden spot for element 'i' -> (n - 1) elements left -> f(n - 1)
    long long int ans = (1LL * (n - 1) * ((usingRecursion(n - 1) % MOD) + (usingRecursion(n - 2) % MOD))) % MOD;

    return ans;
}

long long int countDerangements(int n) {
    cout << "using recursion: " << usingRecursion(n) << endl;

    vector<long long int> dp(n + 1, -1);
    cout << "using memoization: " << usingMemoization(n, dp) << endl;

    cout << "using tabulation: " << usingTabulation(n) << endl;
}

int main() {
    int n = 4;

    countDerangements(n);
    return 0;
}