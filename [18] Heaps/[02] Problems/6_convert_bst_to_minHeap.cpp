#include <bits/stdc++.h>
#include "../../[17] Binary Search Trees/lib/build.cpp"
using namespace std;

// CONVERT BST TO MIN HEAP
// conditions: 
//      - given BST is a complete binary tree (hint: it means structure will not change only values in it can change)
//      - all values in left sub-tree should be less than all the values in the right subtree of the node

// inorder will give you sorted array of all elements.
// N < L < R therefore we can use preorder to put elements in the tree

void inorder(Node* root, vector<int> &ans) {
    if(root == NULL) return;

    inorder(root -> left, ans);
    ans.push_back(root -> data);
    inorder(root -> right, ans);
}

void fillPreOrder(Node* &root, vector<int> &inorederedNodes, int &index) {
    if(root == NULL) return ;

    root -> data = inorederedNodes[index++];
    fillPreOrder(root -> left, inorederedNodes, index);
    fillPreOrder(root -> right, inorederedNodes, index);
}

void convertBSTtoMinHeap(Node* &root) {
    if(root == NULL) return ;

    // 1. store nodes in ans with inorder (increasing order nodes)
    vector<int> inorderedNodes;
    inorder(root, inorderedNodes);
    
    // 2. fill the BST with preorder
    int index = 0;
    fillPreOrder(root, inorderedNodes, index);
}

int main() {

    Node* root = NULL;
    takeInput(root); // 4 2 6 1 3 5 7 -1

    cout << "original BST: ";
    levelOrderIteratively(root);

    convertBSTtoMinHeap(root);

    cout << "after converting to minHeap: ";
    levelOrderIteratively(root);

    return 0;
}