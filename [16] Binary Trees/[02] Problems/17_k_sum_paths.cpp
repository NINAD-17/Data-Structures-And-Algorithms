#include "../lib/build.cpp"
#include <iostream>
#include <unordered_map>
using namespace std;

// K SUM PATHS
// read this: https://www.geeksforgeeks.org/count-all-k-sum-paths-in-a-binary-tree/

// Optimized approach
// time: O(n)
int pathSum(Node *root, int targetSum) {
    unordered_map<long long, int> prefixCount;

    prefixCount[0] = 1;

    return countPaths(root, 0, targetSum, prefixCount);
}

int countPaths(Node *root, long long currSum, int targetSum,
               unordered_map<long long, int> &prefixCount) {
    if(!root)
        return 0;

    currSum += root->data;
    long long needed = currSum - targetSum;

    int totalPaths = 0;
    if(prefixCount.find(needed) != prefixCount.end()) {
        totalPaths += prefixCount[needed];
    }

    prefixCount[currSum]++;

    totalPaths += countPaths(root->left, currSum, targetSum, prefixCount);

    totalPaths += countPaths(root->right, currSum, targetSum, prefixCount);

    prefixCount[currSum]--;
    if(prefixCount[currSum] == 0) {
        prefixCount.erase(
            currSum); // Completely removes the key from the map
    }

    return totalPaths;
}

// Note: for this problem we've created separate build function
//       because in our example one node contain -1 as a value. see image from readme file. So we modified -2 for return
Node *buildTree22(Node *&root) {
    // initially the root is NULL
    int data;

    if(root == NULL)
        cout << "enter data for root node: ";
    else
        cout << "enter data: ";
    cin >> data;
    cout << endl;

    if(data == -2)
        return NULL;

    root = new Node(data);

    cout << "-> enter data for inserting in left of " << data << endl;
    root->left = buildTree22(root->left);

    cout << "-> enter data for inserting in right of " << data << endl;
    root->right = buildTree22(root->right);

    return root;
}

// Time Complexity: O(n * h)
//   - Skewed tree (worst case): O(n^2)
//   - Balanced tree (best/average case): O(n log n)
// Auxiliary Space Complexity: O(h) — call stack depth and path vector storage
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
void solve(Node *&root, int k, int &count, vector<int> &path) {
    if(root == NULL)
        return;

    path.push_back(root->data);

    solve(root->left, k, count, path);
    solve(root->right, k, count, path);

    int size = path.size();
    int sum = 0;
    for(int i = size - 1; i >= 0; i--) {
        sum += path[i];

        if(sum == k)
            count++;
    }

    // backtrack
    path.pop_back();
}

int kSumPaths(Node *root, int k) {
    if(root == NULL)
        return -1;

    vector<int> path;
    int count = 0;

    solve(root, k, count, path);

    return count;
}

int main() {
    Node *root = NULL;
    root = buildTree22(root); // 1 3 2 -2 -2 1 1 -2 -2 -2 -1 4 1 -2 -2 2 -2 -2 5 -2 6 -2 -2

    // levelOrderIteratively(root);

    cout << "Sum: " << kSumPaths(root, 5) << endl;

    return 0;
}