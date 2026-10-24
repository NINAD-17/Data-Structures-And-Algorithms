#include <iostream>
using namespace std;

// Time complexity: O(n)
long long calcFactorialUsingModularArithmetics(int num) {
    int m = 1e9 + 7; // 1000000000 + 7 = 1000000007 OR (1 × 10^9) + 1. It's a large prime number.
    long long result = 1;

    if(num == 0) return 1;

    while(num != 1)
        result = (result * num--) % m; // This line ensures that result never exceeds m by taking the modulus after each multiplication.
    // result = (result % m * (num--) % m) % m; You can also able to do this. It will not change your result as said in property.
    // Property: (a * b) mod m is equivalent to ((a mod m) * (b mod m)) mod m

    return result;
}

// Time complexity: O(n)
int calcFatorial(int num) {
    int result = 1;

    if(num == 0) return 1;

    while(num != 1) 
        result *= num--;
    
    return result;
}

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    cout << "Factorial of " << num << " is " << calcFatorial(num) << endl;
    cout << "Using Modular Arithmetics ----- \nFactorial of " << num << " is " << calcFactorialUsingModularArithmetics(num) << endl;

    return 0;
}