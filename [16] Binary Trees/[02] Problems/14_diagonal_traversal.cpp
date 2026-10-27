#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "../lib/build.cpp"
using namespace std;

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