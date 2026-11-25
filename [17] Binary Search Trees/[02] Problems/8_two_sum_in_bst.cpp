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

bool twoSumInBST(Node* &root, int target) {
    vector<int> inorderElements;
    inorderTraversal(root, inorderElements);

    int st = 0, en = inorderElements.size() - 1;

    while(st < en) {
        int sum = inorderElements[st] + inorderElements[en];

        if(sum == target) 
            return true;
        else if(sum > target) 
            en--;
        else
            st++;
    }

    return false;
}

int main() {

    return 0;
}