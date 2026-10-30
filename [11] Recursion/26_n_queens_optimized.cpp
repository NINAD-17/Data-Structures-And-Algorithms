#include <iostream>
#include <vector>
using namespace std;

void solve(int col, int n, vector<vector<int>> &board, vector<vector<int>> &ans,
           vector<bool> &rowOccupied,
           vector<bool> &bottomLeftDiagonal,
           vector<bool> &topLeftDiagonal) {

    // Base case: all n queens placed successfully
    if(col == n) {
        vector<int> temp;
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                temp.push_back(board[r][c]);
            }
        }
        ans.push_back(temp);
        return;
    }

    for(int row = 0; row < n; row++) {
        // O(1) Safety Check
        if(!rowOccupied[row] &&
           !bottomLeftDiagonal[row + col] &&
           !topLeftDiagonal[(n - 1) + (col - row)]) {

            // 1. DO: place queen and mark attack paths
            board[row][col] = 1;
            rowOccupied[row] = true;
            bottomLeftDiagonal[row + col] = true;
            topLeftDiagonal[(n - 1) + (col - row)] = true;

            // 2. RECURSE
            solve(col + 1, n, board, ans, rowOccupied, bottomLeftDiagonal, topLeftDiagonal);

            // 3. UNDO: backtrack
            board[row][col] = 0;
            rowOccupied[row] = false;
            bottomLeftDiagonal[row + col] = false;
            topLeftDiagonal[(n - 1) + (col - row)] = false;
        }
    }
}

vector<vector<int>> solveQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<int>> ans;

    // Lookup tables
    vector<bool> rowOccupied(n, false);
    vector<bool> bottomLeftDiagonal(2 * n - 1, false);
    vector<bool> topLeftDiagonal(2 * n - 1, false);

    solve(0, n, board, ans, rowOccupied, bottomLeftDiagonal, topLeftDiagonal);
    return ans;
}
