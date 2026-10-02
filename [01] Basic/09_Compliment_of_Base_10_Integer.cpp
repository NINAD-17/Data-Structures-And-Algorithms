#include <iostream>
#include <math.h>
using namespace std;

// Small Code
int compOfBase10Int(int base10Int) {
    int ans = 0, mask = 0;
    int temp = base10Int;

    while(temp != 0) {
        mask = (mask << 1) | 1;
        temp >>= 1;
    }

    ans = (~base10Int) & mask;
    return ans;
}

// Lengthy code written by me
// This function returns output as a binary number.
int complimentOfBase10Int(int base10Int) {
    int count = 0, ans = 0, i = 1;
    int complimentOfInt = ~base10Int;

    while(base10Int != 0) {
        count++;
        base10Int >>= 1;
    }
    cout << count << " " << base10Int << endl;

    while(count != 0) {
        int bit = complimentOfInt & 1;
        ans += (i * bit);
        i *= 10;
        complimentOfInt >>= 1;
        count--;
    }

    return ans;
}

int main() {

    int base10Int;

    int x = 10;
    cout << "With regular ~ complement of 10 it'll give " << ~x << endl; // But we want different that is 10 = 1010 and ~10 = 0101 which is 5

    // cout << "Enter a number: ";
    // cin >> base10Int;
    base10Int = 10;

    cout << "Compliment of " << base10Int << " is " << complimentOfBase10Int(base10Int) << endl;
    cout << "Compliment of " << base10Int << " is " << compOfBase10Int(base10Int) << endl;

    return 0;
}