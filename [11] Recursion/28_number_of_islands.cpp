#include <bits/stdc++.h>
using namespace std;

// LeetCode 200: Number of Islands
// Time Complexity:  O(M * N)  [Each cell is visited at most once]
// Space Complexity: O(M * N)  [Worst-case DFS recursion stack when entire grid is '1']

void sinkIsland(int r, int c, vector<vector<char>> &grid, int rows, int cols) {
    // Base Case: out of bounds or already water ('0')
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '0') {
        return;
    }

    // Sink current land cell so it is not counted again
    grid[r][c] = '0';

    // Explore all 4 adjacent neighbors (Down, Up, Left, Right)
    sinkIsland(r + 1, c, grid, rows, cols);
    sinkIsland(r - 1, c, grid, rows, cols);
    sinkIsland(r, c - 1, grid, rows, cols);
    sinkIsland(r, c + 1, grid, rows, cols);
}

int numIslands(vector<vector<char>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int islands = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            // Found unvisited land -> new island discovered
            if (grid[r][c] == '1') {
                islands++;
                sinkIsland(r, c, grid, rows, cols);
            }
        }
    }

    return islands;
}

int main() {
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    cout << "Example 1 Islands: " << numIslands(grid1) << endl; // Expected: 1
    cout << "Example 2 Islands: " << numIslands(grid2) << endl; // Expected: 3

    return 0;
}