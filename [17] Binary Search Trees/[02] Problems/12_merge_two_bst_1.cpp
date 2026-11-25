#include <bits/stdc++.h>
#include "../lib/build.cpp"
using namespace std;

// Time: O(m + n)
// Space: O(m + n)

void inorderTraversal(Node* &root, vector<int> &inorderElements) {
    if(root == NULL) return ;

    // Left
    inorderTraversal(root -> left, inorderElements);

    // Node
    inorderElements.push_back(root -> data);

    // Right
    inorderTraversal(root -> right, inorderElements);
}

vector<int> merge2SortedArr(vector<int> &bst1, vector<int> &bst2) {
    vector<int> ans(bst1.size() + bst2.size());

    int i = 0, j = 0, k = 0;
    while(i < bst1.size() && j < bst2.size()) {
        if(bst1[i] < bst2[j])
            ans[k++] = bst1[i++];
        else 
            ans[k++] = bst2[j++];
    }

    while(i < bst1.size())
        ans[k++] = bst1[i++];

    while(j < bst2.size()) 
        ans[k++] = bst2[j++];
    
    return ans;
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

Node* mergeBST(Node* root1, Node* root2) {
    // Step 1: Store Inorder
    vector<int> bst1, bst2;
    inorderTraversal(root1, bst1);
    inorderTraversal(root2, bst2);

    // Step 2: Merge two sorted arrays (bst1, bst2)
    vector<int> mergedArr = merge2SortedArr(bst1, bst2);

    // Step 3: Use merged inorder array to build BST
    int st = 0, en = mergedArr.size() - 1;
    return inorderToBST(st, en, mergedArr);
}


int main() {
    // BST 1:
    //       10
    //      /  \
    //     5    20
    //    / \
    //   2   7
    Node* root1 = new Node(10);
    root1->left = new Node(5);
    root1->right = new Node(20);
    root1->left->left = new Node(2);
    root1->left->right = new Node(7);

    // BST 2:
    //       15
    //      /  \
    //     12   25
    //    /    /
    //   11   18
    Node* root2 = new Node(15);
    root2->left = new Node(12);
    root2->right = new Node(25);
    root2->left->left = new Node(11);
    root2->right->left = new Node(18);

    Node* mergedRoot = mergeBST(root1, root2);

    cout << "Merged Balanced BST (Level Order):" << endl;
    levelOrderIteratively(mergedRoot);

    // Sorted order
    vector<int> sortedCheck;
    inorderTraversal(mergedRoot, sortedCheck);
    cout << "\nInorder Traversal (Sorted Check): ";
    for (int val : sortedCheck) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}