#include <bits/stdc++.h>
using namespace std;

// Count Negetive Numbers In Sorted Matrix: https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/description/

// Staircase Approach
// Time: O(N + M) => O(rows + cols)
// Space: O(1)
int countNegetives(vector<vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int negetiveCount = 0;

    // Choose last element from 1st column (Start climbing stairs from this point)
    int row = rows - 1;
    int col = 0;

    while(row >= 0 && col < cols) {
        if(grid[row][col] < 0) {
            negetiveCount += (cols - col); // Count number from this element to last col
            row--; // If current element is negetive then all next col elements will also be negetive as the order is decreasing order.
        } else {
            col++;
        }
    }

    return negetiveCount;
}

int main() {
    vector<vector<int>> grid = {{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}};

    cout << countNegetives(grid) << endl;

    return 0;
}