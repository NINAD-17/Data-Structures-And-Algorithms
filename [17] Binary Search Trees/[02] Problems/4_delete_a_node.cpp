#include "../lib/build.cpp"
#include <iostream>
using namespace std;

// DELETE A NODE (imp)
// conditions:
//      1. 0 childs
//      2. 1 child in left
//      3. 1 child in right
//      4. 2 childs

Node *findSuccessor(Node *root) {
    Node *temp = root;

    while(temp->left != NULL)
        temp = temp->left;

    return temp;
}

Node *deleteFromBST(Node *root, int data) {
    // base case
    if(root == NULL)
        return root;

    if(root->data == data) {
        // Case 1: 0 children
        if(root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        // Case 2: 1 child -> only left child present
        if(root->left != NULL && root->right == NULL) {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: 1 child -> only right child present
        if(root->left == NULL && root->right != NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        }

        // Case 4: 2 children present
        if(root->left != NULL && root->right != NULL) {
            // Since root->right is guaranteed to exist here, the inorder successor
            // is simply the leftmost (minimum) node in the right subtree
            int mini = findSuccessor(root->right)->data;

            // Replace root's data with the successor's data
            root->data = mini;

            // Delete the duplicate successor node from the right subtree
            root->right = deleteFromBST(root->right, mini);

            return root;
        }
    }
    // recursive calls
    else if(root->data > data) {
        root->left = deleteFromBST(root->left, data);
        return root;
    } else {
        root->right = deleteFromBST(root->right, data);
        return root;
    }

    return root;
}

// More organized code:
Node *findSuccessor2(Node *node) {
    Node *curr = node;
    while(curr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

Node *deleteNode(Node *root, int key) {
    if(!root)
        return nullptr;

    if(key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if(key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Case 1 & 2: 0 children or 1 child (only right child)
        if(!root->left) {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        // Case 3: 1 child (only left child)
        if(!root->right) {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        // Case 4: 2 children
        Node *successor = findSuccessor2(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }

    return root;
}

int main() {
    Node *root = NULL;

    cout << "note: to stop entering the data give input -1" << endl;
    cout << "enter data to create BST: ";
    takeInput(root); // 21 10 50 5 15 40 60 30 45 55 70 -1

    levelOrderIteratively(root);
    cout << endl << endl;

    deleteFromBST(root, 50);
    levelOrderIteratively(root);

    return 0;
}