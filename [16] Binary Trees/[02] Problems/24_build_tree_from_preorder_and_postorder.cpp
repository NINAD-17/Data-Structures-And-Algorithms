#include <iostream>
#include <map>
#include "../lib/node.cpp"
using namespace std;

// CONSTRUCT TREE FROM PREORDER AND POSTORDER (LeetCode 889)

// algorithm:
//      1. take preorder[preStart] as the current root
//      2. if preStart == preEnd, return root (single leaf node)
//      3. preorder[preStart + 1] is the root of the left subtree -> find its position in postorder
//      4. calculate leftSize = leftRootPostIdx - postStart + 1
//      5. call left recursion and right recursion using leftSize boundaries

void createMapping(int *postorder, int n, map<int, int> &nodeToIndex) {
    for(int i = 0; i < n; i++)
        nodeToIndex[postorder[i]] = i; // mapping of node to index
}

Node* solve(int *preorder, int *postorder, map<int, int> &nodeToIndex, int preStart, int preEnd, int postStart, int postEnd) {
    // base case: empty range
    if(preStart > preEnd)
        return NULL;

    // first element in preorder (NLR) is the root
    int element = preorder[preStart];
    Node* root = new Node(element);

    // base case: single node (leaf) -> prevents out-of-bounds on preorder[preStart + 1]
    if(preStart == preEnd)
        return root;

    // next element in preorder is the root of the left subtree
    int leftRootVal = preorder[preStart + 1];

    // find position of left subtree's root in postorder array
    int leftRootPostIdx = nodeToIndex[leftRootVal];
    int leftSize = leftRootPostIdx - postStart + 1;

    // make recursive calls to left and right subtrees
    root -> left = solve(preorder, postorder, nodeToIndex, preStart + 1, preStart + leftSize, postStart, leftRootPostIdx);
    root -> right = solve(preorder, postorder, nodeToIndex, preStart + leftSize + 1, preEnd, leftRootPostIdx + 1, postEnd - 1);

    return root;
}

Node* buildTree(int *preorder, int *postorder, int n) {
    // create mapping between postorder nodes to index
    map<int, int> nodeToIndex;
    createMapping(postorder, n, nodeToIndex);

    Node* ans = solve(preorder, postorder, nodeToIndex, 0, n - 1, 0, n - 1);
    return ans;
}

// post order function to print ans in postorder (LRN)
void postorderTraversal(Node* ans) {
    // base case
    if(ans == NULL)
        return ;

    postorderTraversal(ans -> left);
    postorderTraversal(ans -> right);

    cout << ans -> data << " ";
}

void preorderTraversal(Node* ans) {
    if(ans == NULL)
        return ;

    cout << ans -> data << " ";

    preorderTraversal(ans -> left);
    preorderTraversal(ans -> right);
}

int main() {

    int preorder[7] = {1, 2, 4, 5, 3, 6, 7};
    int postorder[7] = {4, 5, 2, 6, 7, 3, 1};

    Node* ans = buildTree(preorder, postorder, 7);

    cout << "postorder: ";
    postorderTraversal(ans);

    cout << "\npreorder: ";
    preorderTraversal(ans);

    return 0;
}