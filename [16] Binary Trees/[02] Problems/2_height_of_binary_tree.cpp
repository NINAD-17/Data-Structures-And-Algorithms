#include <iostream>
#include "../lib/build.cpp"
using namespace std;

// HEIGHT OF BINARY TREE
// height is the longest path between root node and leaf node

// 1. Recursive Solution
// Time Complexity: O(n)
// Auxillary Space Complexity: O(h)
//   - Balanced Tree: O(log n)
//   - Skewed Tree: O(n)
int heightOfBinTree(Node* &root) {
    if(root == NULL)
        return 0;

    int leftNode = heightOfBinTree(root -> left);
    int rightNode = heightOfBinTree(root -> right);

    return max(leftNode, rightNode) + 1;
}

// 2. Iterative solution using level order traversal
// Time Complexity: O(n) — visits every node exactly once
// Auxiliary Space Complexity: O(w), where w is the maximum width of the tree
//   - In terms of n: O(n) in the worst case (balanced/complete tree holds ~n/2 leaves -  bottom level has roughly n/2 nodes)
//   - Skewed tree: O(1) (queue holds at most 1 element at any time)
int findHeight(Node* &root) {
    if(root == NULL) return 0;

    queue<Node*> q;
    q.push(root);

    int height = 0;

    while(!q.empty()) {
        int currLevelSize = q.size();

        for(int i = 0; i < currLevelSize; i++) {
            Node* front = q.front();
            q.pop();

            if(front -> left) q.push(front -> left);
            if(front -> right) q.push(front -> right);
        }

        height++;
    }

    return height;
}

int main() {
    Node* root = NULL;
    root = buildTree(root); 
    // input 3 levels: 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 -1
    // intput 4 levels: 1 2 4 -1 8 -1 -1 5 -1 -1 3 6 -1 -1 -1

    cout << "height of binary tree is " << heightOfBinTree(root) << " levels" << endl;
    cout << "height of bt using iterative approach " << findHeight(root) << " levels" << endl;

    return 0;
}