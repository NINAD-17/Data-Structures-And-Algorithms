#include <bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, int val, vector<vector<int>> &board, int n) {
    for(int i = 0; i < n; i++) {
        // Row check
        if(board[row][i] == val)
            return false;

        // Col check
        if(board[i][col] == val)
            return false;

        // 3 * 3 matrix check
        if(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == val)
            return false;
    }

    return true;
}

bool solve(vector<vector<int>> &board) {
    int n = board.size();

    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {

            // Look for empty cell
            if(board[row][col] == 0) {
                for(int val = 1; val <= 9; val++) {

                    if(isSafe(row, col, val, board, n)) {
                        board[row][col] = val;

                        // Recurse to solve remaining cells
                        bool isNextSolutionPossible = solve(board);
                        if(isNextSolutionPossible)
                            return true;
                        else
                            board[row][col] = 0; // backtrack
                    }
                }

                // If 1-9 cannot be placed in this empty cell, path is invalid
                return false;
            }
        }
    }

    // No empty cells remaining: Sudoku solved!
    return true;
}

bool solveOptimized(int row, int col, vector<vector<int>> &board) {
    // If we passed the 8th row, the entire board is filled!
    if(row == 9)
        return true;

    // If we reach the end of a row, move to the next row at column 0
    if(col == 9)
        return solveOptimized(row + 1, 0, board);

    // If current cell is already filled, move to next column immediately
    if(board[row][col] != 0) {
        return solveOptimized(row, col + 1, board);
    }

    // Try values 1 to 9
    for(int val = 1; val <= 9; val++) {
        if(isSafe(row, col, val, board, 9)) {
            board[row][col] = val;

            if(solveOptimized(row, col + 1, board)) {
                return true;
            }

            board[row][col] = 0; // Backtrack
        }
    }

    return false; // Triggers backtracking in parent
}

void solveSudoku(vector<vector<int>> &sudoku) {
    solve(sudoku);
}

void printBoard(const vector<vector<int>> &board) {
    for(int r = 0; r < 9; r++) {
        if(r % 3 == 0 && r != 0) {
            cout << "------+-------+------\n";
        }
        for(int c = 0; c < 9; c++) {
            if(c % 3 == 0 && c != 0) {
                cout << "| ";
            }
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Sample Sudoku board (0 represents empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    cout << "Input Sudoku Board:\n";
    printBoard(board);

    if(solve(board)) {
        cout << "\nSolved Sudoku Board:\n";
        printBoard(board);
    } else {
        cout << "\nNo solution exists for the given board.\n";
    }

    return 0;
}