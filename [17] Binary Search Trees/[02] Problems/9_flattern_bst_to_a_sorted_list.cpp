#include <bits/stdc++.h>
#include "../lib/build.cpp"
using namespace std;

void inorderTraversal(Node* &root, vector<Node*> &inorderElements) {
    if(root == NULL) return ;

    // Left
    inorderTraversal(root -> left, inorderElements);

    // Node
    inorderElements.push_back(root);

    // Right
    inorderTraversal(root -> right, inorderElements);
}

Node* flattenBST(Node* &root) {
    vector<Node*> inorderElements;
    inorderTraversal(root, inorderElements);

    int size = inorderElements.size();
    for(int i = 0; i < size - 1; i++) {
        Node* node = inorderElements[i];
        Node* nextNode = inorderElements[i + 1];
        
        node -> left = NULL;
        node -> right = nextNode;
    }

    Node* lastNode = inorderElements[size - 1];
    lastNode -> left = NULL;
    lastNode -> right = NULL;

    Node* newRoot = inorderElements[0];
    return newRoot;
}

int main() {
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);
    Node* node6 = new Node(6);
    Node* node7 = new Node(7);

    node4 -> left = node2;
    node4 -> right = node6;

    node2 -> left = node1;
    node2 -> right = node3;

    node6 -> left = node5;
    node6 -> right = node7;

    Node* root = node4;
    levelOrderIteratively(root);

    Node* newRoot = flattenBST(root);

    Node* curr = newRoot;
    while(curr != NULL) {
        cout << curr -> data << " ";
        curr = curr -> right;
    }

    return 0;
}