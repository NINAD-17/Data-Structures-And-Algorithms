#include <iostream>
#include "../lib/build.cpp"
using namespace std;

// CHECK FOR BALANCED TREE  
// balanced tree means difference between heights of left and right subtrees isn't more than one for all nodes of tree.

int height(Node* root) { // time complexity: O(n)
    if(root == NULL)
        return 0;

    int left = height(root -> left);
    int right = height(root -> right);

    return max(left, right) + 1;
}

// --- Unoptimized Solution ---
// Time Complexity: O(n * h)
//   - Skewed tree (worst case): O(n^2)
//   - Balanced tree (best/average case): O(n log n)
// Auxiliary Space Complexity: O(h) — maximum active recursion stack depth
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
bool isBalanced(Node* root) {
    if(root == NULL)
        return true;

    bool left = isBalanced(root -> left);
    bool right = isBalanced(root -> right);

    bool diff = abs(height(root -> left) - height(root -> right)) <= 1;

    if(left && right && diff)
        return true;
    else    
        return false;
}

// Optimized Solution
// Time Complexity: O(n)
// Auxiliary Space Complexity: O(h) — recursion stack depth
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
pair<bool, int> isBalancedFast(Node* root) {
    if(root == NULL) {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }

    pair<bool, int> left = isBalancedFast(root -> left);
    pair<bool, int> right = isBalancedFast(root -> right);

    bool leftAns = left.first;
    bool rightAns = right.first;

    bool diff = abs(left.second - right.second) <= 1;

    pair<bool, int> ans;
    ans.second = max(left.second, right.second) + 1; // save height
    
    if(leftAns && rightAns && diff)
        ans.first = true;
    else 
        ans.first = false;

    return ans;
}

bool isBalanced_optimized(Node* root) {
    return isBalancedFast(root).first;
}

int main() {

    Node* root = NULL;
    root = buildTree(root); // 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 -1

    cout << isBalanced(root) << endl;
    cout << isBalanced_optimized(root) << endl;

    return 0;
}