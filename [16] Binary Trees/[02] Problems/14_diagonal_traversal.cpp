#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "../lib/build.cpp"
using namespace std;

vector<int> diagonal_2(Node* root) {
    vector<int> ans;
    if(root == nullptr) return ans;

    // Maps diagonal number -> list of node values in strict level-by-level order
    map<int, vector<int>> diagMap;

    // Queue stores {current_node, diagonal_number}
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while(!q.empty()) {
        pair<Node*, int> qData = q.front();
        Node* currNode = qData.first;
        int diag = qData.second;

        q.pop();

        // Record the node in its diagonal bucket
        diagMap[diag].push_back(currNode -> data);

        // Left child shifts to the next diagonal (diag + 1)
        if (currNode -> left) {
            q.push({currNode -> left, diag + 1});
        }

        // Right child stays on the same diagonal (diag)
        if (currNode -> right) {
            q.push({currNode -> right, diag});
        }
    }

    // Flatten the map from diagonal 0, 1, 2, ... into the final answer
    for (auto& [diag, nodes] : diagMap) {
        for (int val : nodes) {
            ans.push_back(val);
        }
    }

    return ans;
}

// If there're 2 elements on exact same position then it won't give output in order by below code.
//             1 (d=0)
//           /         \
//       2 (d=1)       3 (d=0)
//      /      \      /      \
//  4 (d=2)  5 (d=1) 6 (d=1)  7 (d=0)
//            \       \        \
//          8 (d=1)  9 (d=1)  10 (d=0)
//            \
//          11 (d=1)
// Here, 5 and 6 are on diagonal 1 but below code will output 2, 5, 9, 6 instead of 2, 5, 6, 9
vector<int> diagonal(Node *root) {
    vector<int> ans;
    if(root == NULL) return ans;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* curr = q.front();
        q.pop();

        // Traverse the entire right branch (same diagonal)
        while(curr != NULL) {
            ans.push_back(curr->data);

            // Left child starts a new diagonal -> save it in the queue
            if(curr->left) {
                q.push(curr->left);
            }

            // Move to the next node on the same diagonal
            curr = curr->right;
        }
    }

    return ans;
}