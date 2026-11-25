#include <bits/stdc++.h>
#include "../lib/build.cpp"
using namespace std;

void inorderTraversal(Node* &root, vector<int> &inorderElements) {
    if(root == NULL) return ;

    // Left
    inorderTraversal(root -> left, inorderElements);

    // Node
    inorderElements.push_back(root -> data);

    // Right
    inorderTraversal(root -> right, inorderElements);
}

Node* inorderToBST(int st, int en, vector<int> &inorderElements) {
    // Base Case
    if(st > en) return NULL;
    // if (st == en) return new Node(inorderElements[st]); // we can use this for single nodes to reduce recursion overhead

    int mid = (st + en) / 2;
    Node* root = new Node(inorderElements[mid]);

    root -> left = inorderToBST(st, mid - 1, inorderElements);
    root -> right = inorderToBST(mid + 1, en, inorderElements);

    return root;
}

bool balancedBST(Node* &root, int target) {
    vector<int> inorderElements;
    inorderTraversal(root, inorderElements);

    inorderToBST(0, inorderElements.size(), inorderElements);
}

int main() {

    return 0;
}