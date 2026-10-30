#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
// Time Complexity: O(1)
// Auxiliary Space (Extra Space): O(1)
bool isPowerOfTwo_optimal(int n) {
    // n must be positive AND have exactly one set bit
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Time Complexity: O(log n)
// Auxillary Space: O(1)
bool isPowerOfTwo(int n) {
    if (n <= 0)
        return false;

    while (n % 2 == 0) {
        n /= 2;
    }

    return n == 1;
}

int main() {
    int num = 16;

    int ans_1 = isPowerOfTwo(num);
    cout << ans_1 << endl;

    int ans_2 = isPowerOfTwo_optimal(num);
    cout << ans_2 << endl;

    return 0;
}