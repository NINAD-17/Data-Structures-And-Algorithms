#include <iostream>
#include <map>
#include "../lib/node.cpp"
using namespace std;

// CONSTRUCT TREE FROM INORDER AND POSTORDER
// (*hard question)

// algorithm: 
//      1. take index element as a root (from postorder)
//      2. find root element's position in an inorder
//      3. call right recursion from pos + 1 to inorderEnd
//      4. call left recursion from inorderStart to pos - 1 

void createMapping(int *inorder, int n, map<int, int> &nodeToIndex) {
    for(int i = 0; i < n; i++)
        nodeToIndex[inorder[i]] = i; // mapping of node to index
}

Node* solve(int *inorder, int *postorder, int &postorderIndex, map<int, int> &nodeToMap, int inorderStart, int inorderEnd, int n) {
    // base case: postorderIndex is smaller than 0 and inorderStart > inorderEnd
    if(postorderIndex < 0 || inorderStart > inorderEnd) 
        return NULL;

    // find root element => postorder(LRN) therefore last element is the root
    int element = postorder[postorderIndex--];
    Node* root = new Node(element);

    // find position of root element in inorder array
    int pos = nodeToMap[element]; 

    // make recursive calls to right and left
    // as postorderIndex is traversing from last position we need to call right first then left
    root -> right = solve(inorder, postorder, postorderIndex, nodeToMap, pos + 1, inorderEnd, n);
    root -> left = solve(inorder, postorder, postorderIndex, nodeToMap, inorderStart, pos - 1, n);

    return root;
}  

Node* buildTree(int *inorder, int *postorder, int n) {
    int postorderIndex = n - 1;

    // create mapping between nodes to index
    map<int, int> nodeToIndex;
    createMapping(inorder, n, nodeToIndex);

    Node* ans = solve(inorder, postorder, postorderIndex, nodeToIndex, 0, n - 1, n);
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

    int inorder[8] = {4, 8, 2, 5, 1, 6, 3, 7};
    int postorder[8] = {8, 4, 5, 2, 6, 7, 3, 1};

    Node* ans = buildTree(inorder, postorder, 8);

    cout << "postorder: ";
    postorderTraversal(ans);

    cout << "\npreorder: ";
    preorderTraversal(ans);

    return 0;
}