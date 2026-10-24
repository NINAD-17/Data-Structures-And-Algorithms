#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Step 1: Standard Sieve to compute all base primes up to floor(sqrt(num))
vector<int> simpleSieve(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Step 2: Segmented Sieve to process remaining numbers in blocks
void segmentedSieve(int num) {
    if (num < 2) return;

    // Use floor(sqrt(num)) to define the block size cleanly
    int limit = floor(sqrt(num));

    // Base primes <= sqrt(num)
    vector<int> primes = simpleSieve(limit);

    // Print all base primes directly (no duplicates later)
    for (int p : primes) {
        cout << p << " ";
    }

    // Segments strictly start AFTER the base primes range
    int low = limit + 1;
    int high = low + limit - 1; // inclusive upper bound: [low, high]

    while (low <= num) {
        // Cap the upper bound so we don't exceed 'num'
        if (high > num) {
            high = num;
        }

        // Window width is (high - low + 1), avoiding extra memory allocation
        int windowSize = high - low + 1;
        vector<bool> mark(windowSize, true);

        // Cancel multiples using only the precomputed base primes
        for (int p : primes) {
            // Find the smallest multiple of p that is >= low
            long long start = ((long long)low / p) * p;
            if (start < low) {
                start += p;
            }

            // Optimization & safety: Start at p * p because all smaller multiples
            // (2*p, 3*p, etc.) were already cancelled by primes smaller than p.
            start = max(start, (long long)p * p);

            // Mark all multiples of p in current window [low, high]
            for (long long j = start; j <= high; j += p) {
                mark[j - low] = false; // Offset indexing: maps number 'j' -> index 'j - low'
            }
        }

        // Print primes discovered in the current block
        for (int i = low; i <= high; i++) {
            if (mark[i - low]) {
                cout << i << " ";
            }
        }

        // Slide the window forward to the next disjoint segment
        low = high + 1;
        high = low + limit - 1;
    }

    cout << endl;
}

int main() {
    int num = 105;
    cout << "Primes up to " << num << ":\n";
    segmentedSieve(num);
    return 0;
}