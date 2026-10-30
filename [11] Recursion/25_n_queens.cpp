#include <bits/stdc++.h>
using namespace std;

void addSolution(vector<vector<int>> &board, vector<vector<int>> &ans) {
    int n = board.size();
    vector<int> temp;

    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            temp.push_back(board[row][col]);
        }
    }

    ans.push_back(temp);
}

bool isSafe(int row, int col, vector<vector<int>> &board, int n) {
    // Check for same row
    int x = row;
    int y = col;

    while(y >= 0) {
        if(board[x][y] == 1)
            return false;
        y--;
    }

    // Check for same diagonal (up left)
    x = row;
    y = col;

    while(x >= 0 && y >= 0) {
        if(board[x][y] == 1)
            return false;
        y--;
        x--;
    }

    // Check for Diagonal (down left)
    x = row;
    y = col;

    while(x < n && y >= 0) {
        if(board[x][y] == 1)
            return false;
        y--;
        x++;
    }

    return true;
}

void solve(int col, vector<vector<int>> &ans, vector<vector<int>> &board, int n) {
    // Base Case
    if(col == n) {
        addSolution(board, ans);
        return;
    }

    // Solve one case and rest recursion will take care
    for(int row = 0; row < n; row++) {
        if(isSafe(row, col, board, n)) {
            board[row][col] = 1;
            solve(col + 1, ans, board, n);

            // Backtrack
            board[row][col] = 0;
        }
    }
}

vector<vector<int>> solveQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<int>> ans;

    solve(0, ans, board, n);

    return ans;
}

int main() {
    int totalQueens = 4;

    vector<vector<int>> ans = solveQueens(totalQueens);
    
    cout << "Total Solutions Found: " << ans.size() << "\n\n";

    for (int sol = 0; sol < ans.size(); sol++) {
        cout << "Solution " << sol + 1 << ":\n";
        for (int r = 0; r < totalQueens; r++) {
            for (int c = 0; c < totalQueens; c++) {
                // Map 2D coordinate (r, c) to flattened index: r * totalQueens + c
                cout << ans[sol][r * totalQueens + c] << " ";
            }
            cout << "\n";
        }
        cout << "-----------------\n";
    }

    return 0;
}