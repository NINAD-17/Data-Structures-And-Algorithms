#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// -----------
// Fix: Remove sort(ans.begin(), ans.end())
//      If you check the directions in strict alphabetical order: ('D', 'L', 'R', 'U') The paths are naturally discovered in sorted order
// Fix: You can remove visited matrix and use maze directly by updating maze[x][y] = 0 and then again restoring value on backtrack
// -----------

// Time: $O(4^{N^2})$
// Space: O(N^2)
//        visited matrix and recursion both take O(N^2)
bool isSafe(int x, int y, int size, vector<vector<int>> &visited, vector<vector<int>> &maze) {
    // curr location should be in the boundary of maze and it should not be visited and curr location should be open path
    if((x >= 0 && x < size) && (y >= 0 && y < size) && visited[x][y] == 0 && maze[x][y] == 1)
        return true; // safe to go
    else 
        return false;
}

void solve(vector<vector<int>> &maze, int size, vector<string> &ans, int x, int y, vector<vector<int>> &visited, string path) {
    // base case: rat has reached the destination
    if(x == size - 1 && y == size - 1) {
        ans.push_back(path);
        return ;
    }

    // you've reached at x,y
    visited[x][y] = 1;

    // choices: up, down, left, right
    // 1. down

    int new_y = y;    int new_x = x + 1;
    if(isSafe(new_x, new_y, size, visited, maze)) {
        path.push_back('D');
        solve(maze, size, ans, new_x, new_y, visited, path);

        // backtrack: remove 'D' from path
        path.pop_back();
    }

    // 2. up
    new_x = x - 1;
    new_y = y;
    if(isSafe(new_x, new_y, size, visited, maze)) {
        path.push_back('U');
        solve(maze, size, ans, new_x, new_y, visited, path);

        // backtrack: remove 'U' from path
        path.pop_back();
    }

    // 3. left
    new_x = x;
    new_y = y - 1;
    if(isSafe(new_x, new_y, size, visited, maze)) {
        path.push_back('L');
        solve(maze, size, ans, new_x, new_y, visited, path);

        // backtrack: remove 'L' from path
        path.pop_back();
    }

    // 4. right
    new_x = x;
    new_y = y + 1;
    if(isSafe(new_x, new_y, size, visited, maze)) {
        path.push_back('R');
        solve(maze, size, ans, new_x, new_y, visited, path);

        // backtrack: remove 'R' from path
        path.pop_back();
    }

    // whenever you go return mark visited as 0
    visited[x][y] = 0;
}

vector<string> findPath(vector<vector<int>> &maze, int size) {
    vector<string> ans; // to store answer

    // illogical case: if src is 0 then rat can't reach src and program can't run.
    if(maze[0][0] == 0) {
        return ans;
    }

    // src co-ordinates (initially)
    int src_x = 0;
    int src_y = 0;

    // make visited vector -> same as maze but all elements are 0
    vector<vector<int>> visited = maze;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            visited[i][j] = 0; // initialized with zero
    }

    string path = ""; // it's string to store path // D for down, U for up, L for left, R for right
    solve(maze, size, ans, src_x, src_y, visited, path);

    // sort the answer
    sort(ans.begin(), ans.end());

    return ans;
}

int main() {

    vector<vector<int>> maze = {{1, 0, 0, 0},
                                {1, 1, 0, 1},
                                {1, 1, 0, 0},
                                {0, 1, 1, 1}};
                            
    int size = 4;
    vector<string> ans = findPath(maze, size);

    for(int i = 0; i < ans.size(); i++)
        cout << i + 1 << ") " << ans[i] << endl;
    cout << endl;

    return 0;
}