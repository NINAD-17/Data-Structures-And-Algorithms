#include <iostream>
#include "../lib/build.cpp"
using namespace std;

// SUM TREE
// A Sum Tree is a binary tree where every non‑leaf node’s value equals the sum of the values of its left and right subtrees.
//      node -> data = sum(left subtree) + sum(right subtree)

// Example:
/*
        20
       /  \
      6    4
     / \   / \
    3   3 3   1
*/
// Node(6) = 3 + 3
// Node(4) = 3 + 1
// Node(20) = 6 + 4 + (all grandchildren sums)


// More optimized approach using short circuit means don't traverse all nodes if you already found that it's not a sum tree
pair<int, bool> isSumTree_3(Node* root) {
    if (root == NULL)
        return {0, true};

    if (root->left == NULL && root->right == NULL)
        return {root->data, true};

    pair<int, bool> leftAns = isSumTree(root->left);
    // Early exit: if left subtree is not a Sum Tree, skip the right subtree completely
    if (!leftAns.second) {
        return {0, false};
    }

    pair<int, bool> rightAns = isSumTree(root->right);
    // Early exit: if right subtree is not a Sum Tree, skip parent validation
    if (!rightAns.second) {
        return {0, false};
    }

    // Now validate the current node
    bool condn = (root->data == leftAns.first + rightAns.first);

    if (condn) {
        return {2 * root->data, true};
    }

    return {0, false};
}


// Optimized Approach
// time complexity: O(n)
// space complexity: O(n)
pair<int, bool> isSumTree(Node* root) {
    // base case
    if(root == NULL)
        return make_pair(0, true);

    // leaf node case
    if(root -> left == NULL && root -> right == NULL)
        return make_pair(root -> data, true);

    pair<int, bool> leftAns = isSumTree(root -> left);
    pair<int, bool> rightAns = isSumTree(root -> right);

    bool left = leftAns.second;
    bool right = rightAns.second;
    bool condn = root -> data == leftAns.first + rightAns.first;

    pair<int, bool> ans;
    if(left && right && condn) {
        ans.second = true;
        ans.first = 2 * (root -> data); // root -> data + left.first + right.first
    } else {
        ans.second = false;
    }

    return ans;
}


// Approach 1:
// Time: O(n^2)
// Space: O(h)
int sum(Node* root) {
    if(root == NULL) return 0;
    return sum(root->left) + sum(root->right) + root->data;
}

bool isSumTree_2(Node* root) {
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return true;

    // get sum of left and right subtrees
    int leftSum = sum(root->left);
    int rightSum = sum(root->right);

    // check current node condition
    bool condn = (root->data == leftSum + rightSum);

    // recursively check left and right subtrees
    return condn && isSumTree_2(root->left) && isSumTree_2(root->right);
}

int main() {

    Node* root = NULL;
    root = buildTree(root); // 20 6 3 -1 -1 3 -1 -1 4 3 -1 -1 1 -1 -1

    pair<int, bool> ans = isSumTree(root);
    cout << ans.first << endl;
    if(ans.second)
        cout << "given tree is a sum tree" << endl;
    else 
        cout << "given tree isn't a sum tree" << endl;

    return 0;
}