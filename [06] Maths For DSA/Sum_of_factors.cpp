#include <iostream>
using namespace std;

// Sum Of Factors
// A factor of a number is a whole number that divides it exactly with no remainder—for example, 3 is a factor of 12 because 12 ÷ 3 = 4.

// Time Complexity: O(sqrt(n))
int sumOfFactors(int num) {
    int sum = 0;

    for(int i = 1; i * i <= num; i++) {
        if((num % i) == 0) {
            sum += i;

            if((num / i) != i)
                sum += (num / i);
        }
    }

    return sum;
}

int main() {
    int num = 16;
    // cin >> num;

    cout << "Sum of factors of " << num << " is " << sumOfFactors(num) << endl;
    return 0;
}