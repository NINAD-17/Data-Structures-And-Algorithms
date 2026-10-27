#include <iostream>
#include "../lib/build.cpp"
using namespace std;

// SUM OF LONGEST BLOODLINE OF A TREE
// SUM OF NODES ON THE LONGEST PATH FROM ROOT TO LEAF NODE
/*
            4
           / \
          2   5
         / \  / \
        7   1 2  3
             \
              6
*/

// --- recursive approach ---
// time complexity: O(n)
// space complexity: O(n)
void solve(Node* root, int currLen, int &maxLen, int currSum, int &maxSum) {
    // base case 
    if(root == NULL) // this case is important because if only one side is NULL then it will go there and can't able to return; so segmentation fault gets
        return ;

    if(root -> left == NULL && root -> right == NULL) {
        currLen++;
        currSum += root -> data;
        
        if(currLen > maxLen) {
            maxLen = currLen;
            maxSum = currSum;
        } else if(currLen == maxLen) {
            maxSum = max(currSum, maxSum);
        }

        return ;
    }

    currSum += root -> data;

    solve(root -> left, currLen + 1, maxLen, currSum, maxSum);
    solve(root -> right, currLen + 1, maxLen, currSum, maxSum);
}

pair<int, int> sumOfLongestBloodline(Node* &root) {
    if(root == NULL)
        return make_pair(0, 0);

    int currLen = 0; // you can set it to 1 as currLen = 1; to make logic cleaner. if done then remove currLen++ from solve()'s 2nd if case.
    int maxLen = 0;

    int currSum = 0;
    int maxSum = 0;

    solve(root, currLen, maxLen, currSum, maxSum);
    return make_pair(maxLen, maxSum);
}

int main() {

    // Node* root = NULL;
    // root = buildTree(root);

    // create nodes manually
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(5);

    root->left->left = new Node(7);
    root->left->right = new Node(1);
    root->left->right->left = new Node(6);

    root->right->left = new Node(2);
    root->right->right = new Node(3);

    // visualize tree
    levelOrderIteratively(root);

    pair<int, int> ans = sumOfLongestBloodline(root);
    cout << "Sum of longest blood line is " << ans.second << " & maximum lenght path is " << ans.first << endl;

    return 0;
}