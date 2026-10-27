#include <iostream>
#include "../lib/build.cpp"
using namespace std;

// DIAMETER (WIDTH) OF BINARY TREE
// Diameter is a longest path between two end nodes. End node can be a leaf node or a root node.
// To find solution we've 3 options:
//      1. find diameter of left tree
//      2. find diameter of right tree
//      3. find height of both tree (left and right)

int height(Node* &root) {
    // base case
    if(root == NULL)
        return 0;

    int leftNode = height(root -> left);
    int rightNode = height(root -> right);

    return max(leftNode, rightNode) + 1;
}

// --- Unoptimized Solution ---
// Time Complexity: O(h * n)
//   - Worst Case (Skewed tree): O(n^2)
//   - Best/Average Case (Balanced tree): O(n log n)
// Auxiliary Space Complexity: O(h) (maximum depth of recursion call stack)
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
int diameter(Node* &root) {
    // base case
    if(root == NULL)
        return 0;

    int op1 = diameter(root -> left); // find longest diameter in left side of tree
    int op2 = diameter(root->right);  // find longest diameter in right side of tree
    int op3 = height(root -> left) + height(root -> right) + 1; // find longest diameter present in combination of both left and right part of tree

    int ans = max(op1, max(op2, op3));
    return ans;
}

// with comments:
int diameterWithComments(Node* root) {
    if(root == NULL)
        return 0;

    cout << "\n------> Recursive call for " << root -> data << endl;
    int leftCnt = diameterWithComments(root -> left);
    cout << "leftCnt: " << leftCnt << "\tfor node: " << root -> data << endl;

    int rightCnt = diameterWithComments(root -> right);
    cout << "rightCnt: " << rightCnt << "\tfor node: " << root -> data << endl;

    int leftHeight = height(root -> left);
    int rightHeight = height(root -> right);
    cout << "leftHeight: " << leftHeight << "\t" << "rightHeight: " << rightHeight << endl;
    int height = leftHeight + rightHeight + 1;
    cout << "height: " << height << "\tfor node: " << root -> data << endl;

    cout << "returning value: " << max(leftCnt, max(rightCnt, height)) << endl << endl;
    return max(leftCnt, max(rightCnt, height));
}

// --- Optimized Solution ---
// Returns pair<int, int> where:
//   first  = diameter of the subtree
//   second = height of the subtree
// Time Complexity: O(n) — visits each node exactly once
// Auxiliary Space Complexity: O(h) — recursion stack depth
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
pair<int, int> diameterFast(Node* &root) {
    // base case
    if(root == NULL) {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }

    pair<int, int> left = diameterFast(root -> left);
    pair<int, int> right = diameterFast(root -> right);

    int op1 = left.first; // accessing diameter
    int op2 = right.first;
    int op3 = left.second + right.second + 1;

    // store answer
    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3)); // store diameter
    ans.second = max(left.second, right.second) + 1; // store height

    return ans;
}

int diameter_optimized(Node* &root) {
    return diameterFast(root).first;
}

int main() {

    Node* root = NULL;
    root = buildTree(root); // 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 -1

    cout << "diameter of binary tree is " << diameter(root) << endl;
    cout << "diameter of binary tree is " << diameter_optimized(root) << endl;

    cout << endl << endl;
    cout << "Diameter With Comments: " << diameterWithComments(root) << endl;

    return 0;
}