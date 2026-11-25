#include <iostream>
#include <vector>
#include <climits>
#include "../lib/build.cpp"
using namespace std;

// IS A VALID BST?


// Simplified code: https://leetcode.com/problems/validate-binary-search-tree/
bool isValid(Node* root, long long min, long long max) {
    if(!root)
        return true;

    // Invalid condition
    if(root -> data <= min || root -> data >= max)
        return false;
        
    return isValid(root -> left, min, root -> data) && isValid(root -> right, root -> data, max);
}

bool isValidBST_2(Node* root) {
    return isValid(root, LLONG_MIN, LLONG_MAX);
}

// approach: with the help of range
// time complexity: O(n)
// space complexity: O(h)
bool isBST(Node* root, int min, int max) {
    if(root == NULL)
        return true;

    if(root -> data >= min && root -> data <= max) {
        bool left = isBST(root -> left, min, root -> data);
        if(left == false)
            return false;

        bool right = isBST(root -> right, root -> data, max);
        return left && right;
    } else 
        return false;
}

bool validateBST(Node* root) {
    return isBST(root, INT_MIN, INT_MAX);
}

// using inorder approach
bool isSorted(vector<int> &ans) {
    for(int i = 0; i < ans.size() - 1; i++) {
        if(ans[i] > ans[i + 1])
            return false;
    }
    return true;
}

void inorder(Node* root, vector<int> &ans) {
    // base case
    if(root == NULL)
        return ;

    inorder(root -> left, ans);

    // store all the nodes data in ans
    ans.push_back(root -> data);

    inorder(root -> right, ans);
}

bool isValidBST(Node* root) {
    vector<int> ans;

    // inorder gives sorted order of nodes. we're storing all nodes in ans vector inorder wise
    inorder(root, ans);

    // if the ans vector is sorted means it's valid BST
    return isSorted(ans);
}

int main() {

    Node* root = NULL;

    cout << "note: to stop entering the data give input -1" << endl;
    cout << "enter data to create BST: ";
    takeInput(root);

    levelOrderIteratively(root);

    cout << endl;
    
    if(validateBST(root))
        cout << "it's a valid BST" << endl;
    else
        cout << "it's not a valid BST" << endl;

    return 0;
}