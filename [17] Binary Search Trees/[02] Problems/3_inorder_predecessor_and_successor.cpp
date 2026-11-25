#include "../lib/build.cpp"
#include <iostream>
using namespace std;

// INORDER PREDECESSOR AND SUCCESSOR IN BST
// Predecessor = largest value < key  (either rightmost in left subtree, OR last ancestor where we turned right)
// Successor   = smallest value > key (either leftmost in right subtree, OR last ancestor where we turned left)
// *Read explanation in README.md file.

// 1. Recursive Approach (Handles both subtree case and ancestor case)
void findPreSuccRecursive(Node *root, Node *&predecessor, Node *&successor, int key) {
    if(root == NULL)
        return;

    // Case 1: Key found -> check left & right subtrees (your rule!)
    if(root->data == key) {
        if(root->left != NULL) {
            Node *temp = root->left;
            while(temp->right != NULL)
                temp = temp->right;
            predecessor = temp;
        }

        if(root->right != NULL) {
            Node *temp = root->right;
            while(temp->left != NULL)
                temp = temp->left;
            successor = temp;
        }
        return;
    }

    // Case 2: Key is smaller -> current root is a potential successor, go left
    if(root->data > key) {
        successor = root;
        findPreSuccRecursive(root->left, predecessor, successor, key);
    }
    // Case 3: Key is larger -> current root is a potential predecessor, go right
    else {
        predecessor = root;
        findPreSuccRecursive(root->right, predecessor, successor, key);
    }
}

// 2. Iterative Approach — O(H) time, O(1) space (No recursion stack, safe if key is missing)
void findPreSuccIterative(Node *root, Node *&predecessor, Node *&successor, int key) {
    predecessor = NULL;
    successor = NULL;
    Node *curr = root;

    while(curr != NULL) {
        if(curr->data == key) {
            // Maximum in left subtree
            if(curr->left != NULL) {
                Node *temp = curr->left;
                while(temp->right != NULL)
                    temp = temp->right;
                predecessor = temp;
            }
            // Minimum in right subtree
            if(curr->right != NULL) {
                Node *temp = curr->right;
                while(temp->left != NULL)
                    temp = temp->left;
                successor = temp;
            }
            break;
        } else if(curr->data > key) {
            successor = curr; // Potential successor before turning left
            curr = curr->left;
        } else {
            predecessor = curr; // Potential predecessor before turning right
            curr = curr->right;
        }
    }
}

int main() {
    Node *root = NULL;
    cout << "Enter data to create BST (-1 to stop): ";
    takeInput(root); // 21 10 50 5 15 40 60 30 45 55 70 -1

    levelOrderIteratively(root);
    cout << endl;

    int key = 45; // Try both 50 (internal node) and 45 (leaf node)
    Node *predecessor = NULL;
    Node *successor = NULL;

    findPreSuccIterative(root, predecessor, successor, key);

    cout << "Predecessor of " << key << ": " << (predecessor ? to_string(predecessor->data) : "None") << endl;
    cout << "Successor of " << key << ": " << (successor ? to_string(successor->data) : "None") << endl;

    return 0;
}