#include "../lib/build.cpp"
#include <iostream>
using namespace std;

// LOWEST COMMON ANCESTOR IN BINARY TREE
// time complexity: O(n)
// space complexity: O(h)

Node *lowestCommonAncestor(Node *root, int n1, int n2) {
    // base case
    if(root == NULL)
        return NULL;

    if(root->data == n1 || root->data == n2) {
        return root;
    }

    Node *leftAns = lowestCommonAncestor(root->left, n1, n2);
    Node *rightAns = lowestCommonAncestor(root->right, n1, n2);

    if(leftAns != NULL && rightAns != NULL)
        return root;
    else if(leftAns != NULL && rightAns == NULL)
        return leftAns;
    else if(leftAns == NULL && rightAns != NULL)
        return rightAns;
    else
        return NULL;
}

// LeetCode 1644: Lowest Common Ancestor of a Binary Tree II
// Condition: n1 or n2 isn't guaranteed so traverse whole tree
Node *findLCA(Node *root, int n1, int n2, bool &found1, bool &found2) {
    if(root == NULL)
        return NULL;

    // 1. Post-order traversal: ALWAYS visit left and right first
    // Never return early, so we explore subtrees even if root matches n1 or n2
    Node *leftAns = findLCA(root->left, n1, n2, found1, found2);
    Node *rightAns = findLCA(root->right, n1, n2, found1, found2);

    // 2. Check if the current node matches n1 or n2
    bool isCurrentTarget = false;
    if(root->data == n1) {
        found1 = true;
        isCurrentTarget = true;
    }
    if(root->data == n2) {
        found2 = true;
        isCurrentTarget = true;
    }

    // 3. If current node is one of the targets, it bubbles up
    if(isCurrentTarget) {
        return root;
    }

    // 4. If targets are found in both left and right subtrees, root is the LCA
    if(leftAns != NULL && rightAns != NULL) {
        return root;
    }

    // 5. Otherwise, pass up whichever subtree found a target
    return (leftAns != NULL) ? leftAns : rightAns;
}

Node *lca(Node *root, int n1, int n2) {
    bool found1 = false;
    bool found2 = false;

    Node *ans = findLCA(root, n1, n2, found1, found2);

    if(found1 && found2)
        return ans;

    return NULL;
}

int main() {
    Node *root = NULL;
    root = buildTree(root); // input: 4 -1 10 5 4 7 -1 -1 8 12 -1 -1 9 -1 -1 3 22 -1 -1 27 29 -1 -1 -1 -1
    levelOrderIteratively(root);

    int n1 = 8;
    int n2 = 27;

    cout << "\nlowest common ancestor of " << n1 << " & " << n2 << " is " << lowestCommonAncestor(root, n1, n2)->data << endl;
    return 0;
}