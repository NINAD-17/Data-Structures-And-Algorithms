#include <iostream>
#include <vector>
using namespace std;

// -- Prime Factorization
//    Prime factorization means expressing a number as a product of prime numbers only.
// Ex - 36 = 2 × 2 × 3 × 3
//      60 = 2 × 2 × 3 × 5
// common: 2 × 2 × 3
// GCD: 2 × 2 × 3 = 12

// Time complexity (worst than brute force solution used in gcd.cpp): O(√num1 + √num2 + k1 × k2) ... here (k1 = factor1.size() and k2 = factor2.size()) [UPDATE - added less time complexity solution below]
// Space complexity: O(k1 + k2)
//      - Storing prime factors of both numbers → O(k1 + k2)
//      - used[] array → O(k2)

vector<int> getPrimeFactors(int num) {
    vector<int> factors;
    for(int i = 2; i * i <= num; i++) { // Runs up to √n → O(√n)
        while(num % i == 0) {
            factors.push_back(i);
            num /= i;
        }
    }
    if(num > 1) factors.push_back(num); // num itself is prime
    return factors;
}

int findGCD_UsingPrimeFactorization(int num1, int num2) {
    vector<int> factors1 = getPrimeFactors(num1);
    vector<int> factors2 = getPrimeFactors(num2);

    int gcd = 1;
    vector<bool> used(factors2.size(), false);

    for(int i = 0; i < factors1.size(); i++) { // 0 to k1.
        for(int j = 0; j < factors2.size(); j++) { // 0 to k2.
            if(!used[j] && factors1[i] == factors2[j]) {
                gcd *= factors1[i];
                used[j] = true;
                break;
            }
        }
    }

    return gcd;
}

// With less time complexity
// Time: O(√num1 + √num2 + k1 + k2)
int findGCD_TwoPointers(int num1, int num2) {
    vector<int> f1 = getPrimeFactors(num1);
    vector<int> f2 = getPrimeFactors(num2);

    int gcd = 1;
    int i = 0, j = 0;

    while (i < f1.size() && j < f2.size()) {
        if (f1[i] == f2[j]) {
            gcd *= f1[i];
            i++;
            j++;
        } else if (f1[i] < f2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return gcd;
}

int main() {
    int num1 = 36, num2 = 60;
    cout << "GCD using prime factorization: " << findGCD_UsingPrimeFactorization(num1, num2) << endl;
    return 0;
}
