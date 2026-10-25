#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// total possible permutations are n! where n is the size of arr => 3! = 6


// Recursive Solution
// Time: O(n * n!)      
// Auxillary Space: O(n) because of recursion stack
//      Total Space: O(n * n!)  You store all n! permutations, each of length n → O(n · n!).
void solve(vector<int> arr, int size, vector<vector<int>> &ans, int index) {
    // Base Case
    if(index >= size) { 
        ans.push_back(arr);
        return ;
    }

    for(int j = index; j < arr.size(); j++) {
        swap(arr[index], arr[j]);
        solve(arr, size, ans, index + 1);
        // Backtrack
        swap(arr[index], arr[j]);
    }
}

vector<vector<int>> permute(vector<int> arr, int size) {
    vector<vector<int>> ans;
    int index = 0; 

    solve(arr, size, ans, index);
    return ans;
}

// Iterative Solution
// Time: O(n * n!)      Space: O(n * n!)
vector<string> permute_iterative(string str) {
    vector<string> ans;
    sort(str.begin(), str.end()); // start with lexicographically smallest
    do {
        ans.push_back(str);
    } while(next_permutation(str.begin(), str.end()));
    return ans;
}

int main() {
    vector<int> arr = {1, 2, 3};
    int size = 3;

    vector<vector<int>> permutations = permute(arr, size);

    // Output
    for(int i = 0; i < permutations.size(); i++) {
        for(int j = 0; j < permutations[i].size(); j++) 
            cout << permutations[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}