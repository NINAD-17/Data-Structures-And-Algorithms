#include <bits/stdc++.h>
using namespace std;

// Brute Force:
// Time: O(n^2 log n)
// Space: O(n^2)
int kthSmallest(vector<vector<int>> &matrix, int k) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<int> elements;

    // Brute Force
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            elements.push_back(matrix[i][j]);
        }
    }

    sort(elements.begin(), elements.end());

    return elements[k - 1];
}