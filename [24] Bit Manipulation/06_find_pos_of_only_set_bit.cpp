#include <bits/stdc++.h>
using namespace std;

// Find position of only set bit

// Time: O(1)
// Space: O(1)
int findPosition(int n) {
    if(n <= 0)
        return -1;

    int count = 0;
    int position = 0;
    int currentPos = 1;

    while(n > 0) {
        if(n & 1) {
            count++;
            position = currentPos;
        }
        if(count > 1) {
            return -1; // Early exit if more than one set bit
        }
        n >>= 1;
        currentPos++;
    }

    return (count == 1) ? position : -1;
}

// Time Complexity: O(log n)
// Space: O(1)
int findPosOfSetBit(int num) {
    if(num == 0 || ((num & (num - 1)) != 0))
        return -1;

    int pos = 1;
    while((num & 1) == 0) {
        num >>= 1;
        pos++;
    }

    return pos;
}

int main() {
    int n = 8;

    cout << findPosOfSetBit(n) << endl;

    return 0;
}