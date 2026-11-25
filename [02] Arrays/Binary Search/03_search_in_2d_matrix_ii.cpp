#include <bits/stdc++.h>
using namespace std;

// Search In 2D Matrix II: https://leetcode.com/problems/search-a-2d-matrix-ii/description/

// Staircase Approach
// Time: O(N + M)
// Space: O(1)
bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int row = rows - 1;
    int col = 0;

    while(row >= 0 && col < cols) {
        if(matrix[row][col] == target)
            return true;
        else if(matrix[row][col] < target)
            col++;
        else
            row--;
    }

    return false;
}

int main() {
    vector<vector<int>> matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};

    if(searchMatrix(matrix, 5))
        cout << "Found!" << endl;
    else 
        cout << "Not Found!" << endl;
    
        return 0;
}