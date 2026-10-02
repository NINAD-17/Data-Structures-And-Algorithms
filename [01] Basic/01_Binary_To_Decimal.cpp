#include <iostream>
#include <math.h>
using namespace std;

// Time Complexity:  O(log(n))
// Space complexity: O(1)
int binToDec_without_pow(int binaryNo) {
    int ans = 0, i = 1;

    while(binaryNo != 0) {
        int digit = binaryNo % 10;
        ans += digit * i;
        binaryNo /= 10;
        i *= 2; // next power of 2
    }
}

// Time Complexity:  O(log(n))
// Space complexity: O(1)
int binToDec(int binaryNo) {
    int ans = 0, i = 0;

    while(binaryNo != 0) {
        int digit = binaryNo % 10;
        ans += pow(2, i++) * digit; // pow() takes O(1) time
        binaryNo /= 10;
    }

    return ans;
}

// Unoptimized Approach:

// Time Complexity - O(exponent)
int getPowOf(int base, int exponent) {
    int ans = 1;
    for(int i = 0; i < exponent; i++) ans *= base;
    return ans;
}

// Time Complexity - O((log n)^2) - Explanation in README.md
int binToDec_2(int binaryNo) {
    int ans = 0, i = 0;

    while(binaryNo != 0) {
        int digit = binaryNo % 10;
        ans += getPowOf(2, i++) * digit;
        binaryNo /= 10;
    }

    return ans;
}

int main() {

    int binaryNo;

    cout << "Enter a binary number: ";
    cin >> binaryNo;

    cout << "Decimal representation of binary number " << binaryNo << " is " << binToDec(binaryNo) << endl;
    return 0;
}