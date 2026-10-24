#include <iostream>
#include <vector>
using namespace std;

// Calculates number of labeled binary trees of size n: C(n) * n!
long long countLabeledBinaryTrees(int n) {
    if (n <= 1) return 1;

    // Step 1: Compute Catalan numbers up to n using DP
    vector<long long> C(n + 1, 0);
    C[0] = 1;
    C[1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            C[i] += C[j] * C[i - 1 - j];
        }
    }

    // Step 2: Compute n! (factorial)
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    // Total = Catalan(n) * n!
    return C[n] * fact;
}

int main() {
    int n = 3;
    cout << "Unlabeled shapes C(3): " << 5 << endl;
    cout << "Labeled trees with 3 nodes: " << countLabeledBinaryTrees(n) << endl; 
    // 5 * 3! = 5 * 6 = 30
    return 0;
}