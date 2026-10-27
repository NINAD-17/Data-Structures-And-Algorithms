#include <bits/stdc++.h>
#include "../lib/node.cpp"
using namespace std;

// Morris Traversal
// Morris Traversal allows us to achieve O(1) auxiliary space by temporarily converting the binary tree into a threaded binary tree.

// Time: O(N) at most each node gets visited 3 times so 3N
// Space: O(1)


// Inorder
void morris_traversal_inorder(Node* root) {
    Node* curr = root;

    while(curr != nullptr) {
        if(curr -> left == nullptr) {
            // If no left child, visit this node and go right
            cout << curr -> data << " ";
            curr = curr -> right;
        } else {
            // Find the inorder predecessor of curr
            Node* prev = curr -> left;

            while(prev -> right != nullptr && prev -> right != curr)
                prev = prev -> right;

            // Make curr the right child of its inorder predecessor
            if(prev -> right == nullptr) {
                prev -> right = curr;
                curr = curr -> left;
            } else {
                // Revert the changes made in the tree structure
                prev -> right = nullptr;
                cout << curr -> data << " ";
                curr = curr -> right;
            }
        }
    }
}

// Preorder
void morris_traversal_preorder(Node* root) {
    Node* curr = root;

    while(curr != nullptr) {
        if(curr -> left == nullptr) {
            // If no left child, visit this node and go right
            cout << curr -> data << " ";
            curr = curr -> right;
        } else {
            // Find the inorder predecessor of curr
            Node* prev = curr -> left;

            while(prev -> right != nullptr && prev -> right != curr)
                prev = prev -> right;

            // Make curr the right child of its inorder predecessor
            if(prev -> right == nullptr) {
                cout << curr -> data << " ";
                prev -> right = curr;
                curr = curr -> left;
            } else {
                // Revert the changes made in the tree structure
                prev -> right = nullptr;
                curr = curr -> right;
            }
        }
    }
}

// Postorder
void morris_traversal_postorder(Node* root) {
    vector<int> postorder;
    Node* curr = root;

    while(curr != nullptr) {
        if(curr -> right == nullptr) {
            postorder.push_back(curr -> data);
            curr = curr -> left;
        } else {
            // Find the inorder predecessor of curr
            Node* prev = curr -> right;

            while(prev -> left != nullptr && prev -> left != curr)
                prev = prev -> left;

            // Make curr the right child of its inorder predecessor
            if(prev -> left == nullptr) {
                postorder.push_back(curr -> data);
                prev -> left = curr;
                curr = curr -> right;
            } else {
                // Revert the changes made in the tree structure
                prev -> left = nullptr;
                curr = curr -> left;
            }
        }
    }

    // Reverse (Root -> Right -> Left) to get (Left -> Right -> Root)
    reverse(postorder.begin(), postorder.end());

    for(auto i: postorder)
        cout << i << " ";
    cout << endl;
}

int main() {

    return 0;
}