#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
// Time Complexity: O(number of set bits)
// Auxiliary Space (Extra Space): O(1)
int minBitFlips_2(int start, int goal) {
    int diff = start ^ goal;

    int count = 0;

    while (diff != 0) {
        diff &= (diff - 1);
        count++;
    }

    return count;
}

// Time Complexity: O(1) 32 iterations
// Auxillary Space: O(1)
int minBitFlips(int start, int goal) {
    int count = 0;

    if (start == goal)
        return count;

    for (int bit = 0; bit < 32; bit++) {
        int currBit = (start >> bit) & 1;

        if (currBit != ((goal >> bit) & 1))
            count++;
    }

    return count;
}

int main() {
    int start = 10, goal = 7;

    int ans_1 = minBitFlips(start, goal);
    cout << ans_1 << endl;

    int ans_2 = minBitFlips_2(start, goal);
    cout << ans_2 << endl;

    return 0;
}