#include <iostream>
#include <vector>
using namespace std;

// Using Sieve of Eratosthenes
// Time Complexity: O(n log (log n)). 
//      This is because the Sieve of Eratosthenes algorithm runs in this time complexity. 
//      The outer loop runs n times and the inner loop runs approximately n / i times, where i is the current prime number. 
//      The sum of n / i for all i from 2 to n is approximately n log log n.
// Space Complexity: O(n)
int countPrimesUsingSOE(int num) {
    int count = 0;

    // Assume every number is prime initially
    vector<bool> prime(num + 1, true); // num + 1 because in arr/vector indexing starts from 0. if we take it as `num` then 50 - 1 = 49 means it can't take 50 in it (0 to 49).

    // 0 and 1 are not prime
    prime[0] = prime[1] = false;

    // Process only till sqrt(num)
    for(int i = 2; i * i <= num; i++) {

        // If i is still prime, mark all multiples of i as composite
        //      Start from i*i because all smaller multiples
        //      (2*i, 3*i, ..., (i-1)*i) were already marked when processing smaller factors.
        if(prime[i]) {
            for (int j = i * i; j <= num; j += i) 
                prime[j] = false;
        }
    }

    cout << "Printing all prime numbers: ";
    for(int i = 2; i <= num; i++) {
        if(prime[i] == true) {
            cout << i << " ";
            count++;
        }
    }
    cout << endl;

    return count;
}


int main() {
    int num;
    cin >> num;

    int totalPrimeNumbers = countPrimesUsingSOE(num);
    cout << "Number of prime numbers which are strictly less than " << num << " is " << totalPrimeNumbers << endl;

    return 0;
}