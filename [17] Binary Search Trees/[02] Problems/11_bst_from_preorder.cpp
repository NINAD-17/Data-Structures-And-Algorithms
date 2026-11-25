#include <bits/stdc++.h>
#include "../lib/build.cpp"
using namespace std;

Node* solve(vector<int> &preorder, int min, int max, int &index) {
    if(index > preorder.size()) return NULL;

    if(preorder[index] < min || preorder[index] > max) return NULL;

    Node* root = new Node(preorder[index++]);

    root -> left = solve(preorder, min, root -> data, index);
    root -> right = solve(preorder, root -> data, max, index);
}

Node* preorderToBST(vector<int> &preorder) {
    int min = INT_MIN;
    int max = INT_MAX;
    int index = 0;

    solve(preorder, min, max, index);
}

int main() {

    vector<int> preorder = {20, 10, 5, 15, 13, 35, 30, 42};
    
    preorderToBST(preorder);

    return 0;
}