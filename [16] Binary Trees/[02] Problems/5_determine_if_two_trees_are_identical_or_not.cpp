#include <iostream>
#include "../lib/build.cpp"
using namespace std;

// DETERMINE IF TWO TREES ARE IDENTICAL OR NOT

// 1. Recursive (Post-order Style)
// Time Complexity: O(min(n1, n2)) — in the worst case (identical trees), O(n) where all nodes are visited
// Auxiliary Space Complexity: O(h) recursion stack depth, where h is the tree height
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
bool isIdentical(Node* root1, Node* root2) {
    // base cases
    if(root1 == NULL && root2 == NULL)
        return true;
    
    if((root1 != NULL && root2 == NULL) || (root1 == NULL && root2 != NULL))
        return false;

    // now both root1 & root2 are non-NULL
    bool left = isIdentical(root1 -> left, root2 -> left);
    bool right = isIdentical(root1 -> right, root2 -> right);

    bool value = root1 -> data == root2 -> data;

    if(left && right && value)
        return true;
    else 
        return false;
}

// 2. Recursive (Pre-order)
// Time Complexity: O(min(n1, n2)) — worst case O(n); faster in practice as it rejects value mismatches early
// Auxiliary Space Complexity: O(h) recursion stack depth, where h is the tree height
//   - Skewed tree: O(n)
//   - Balanced tree: O(log n)
bool isIdentical_traversal(Node* root1, Node* root2) {
    // base cases
    if(root1 == NULL && root2 == NULL) return true;
    if(root1 == NULL || root2 == NULL) return false;

    // compare current node
    if(root1 -> data != root2 -> data) return false;

    // recursively compare left and right subtrees
    return isIdentical_traversal(root1 -> left, root2 -> left) &&
           isIdentical_traversal(root1 -> right, root2 -> right);
}

// 3. Iterative (Level-order / BFS)
// Time Complexity: O(min(n1, n2)) — worst case O(n) when trees are identical
// Auxiliary Space Complexity: O(w) queue memory, where w is the maximum width of the tree
//   - Skewed tree: O(1) (queue holds at most 1 element at any level)
//   - Balanced tree: O(n) (widest level holds ~n/2 nodes)
bool isIdentical_it(Node* &root1, Node* &root2) {
    if(root1 == NULL && root2 == NULL) return true;
    if((root1 == NULL && root2 != NULL) || (root1 != NULL && root2 == NULL)) return false;

    queue<Node*> q1;
    queue<Node*> q2;

    q1.push(root1);
    q2.push(root2);

    while(!q1.empty() && !q2.empty()) {
        Node* front1 = q1.front();
        Node* front2 = q2.front();

        q1.pop();
        q2.pop();

        // compare values
        if(front1 -> data != front2 -> data) return false;

        // compare left children
        if((front1 -> left && !front2 -> left) || (!front1 -> left && front2 -> left)) return false;
        if(front1->left && front2->left) {
            q1.push(front1 -> left);
            q2.push(front2 -> left);
        }

        // compare right children
        if((front1->right && !front2->right) || (!front1->right && front2->right)) return false;
        if(front1->right && front2->right) {
            q1.push(front1->right);
            q2.push(front2->right);
        }
    }

    // If one queue is empty but the other isn't → not identical
    return q1.empty() && q2.empty();
}

int main() {

    Node* root1 = NULL;
    Node* root2 = NULL;
    
    root1 = buildTree(root1);
    root2 = buildTree(root2); // 1 2 -1 -1 3 -1 -1

    if(isIdentical(root1, root2))
        cout << "both trees are identical" << endl;
    else 
        cout << "trees aren't identical" << endl;

    return 0;
}