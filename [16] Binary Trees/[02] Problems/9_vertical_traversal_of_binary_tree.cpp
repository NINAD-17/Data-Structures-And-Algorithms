#include "../lib/build.cpp"
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <set>
using namespace std;

// VERTICAL TRAVERSAL OF BINARY TREE

vector<int> verticalOrder(Node *root) {
    map<int, map<int, vector<int>>> nodes; // map <horizontal distance map<level, vector<nodes>>>
    queue<pair<Node *, pair<int, int>>> q; // queue <pair <node, pair<horizontal distance, level>>>
    vector<int> ans;

    if(root == NULL)
        return ans;

    q.push(make_pair(root, make_pair(0, 0)));

    while(!q.empty()) {
        pair<Node *, pair<int, int>> temp = q.front();
        q.pop();

        Node *frontNode = temp.first;
        int horizontal_dist = temp.second.first;
        int level = temp.second.second;

        nodes[horizontal_dist][level].push_back(frontNode->data);

        if(frontNode->left)
            q.push(make_pair(frontNode->left, make_pair(horizontal_dist - 1, level + 1)));

        if(frontNode->right)
            q.push(make_pair(frontNode->right, make_pair(horizontal_dist + 1, level + 1)));
    }

    for(auto i : nodes) {
        for(auto j : i.second) {
            for(auto k : j.second)
                ans.push_back(k);
        }
    }

    return ans;
}

// Leetcode: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/description/
vector<vector<int>> verticalTraversal(Node *root) {
    vector<vector<int>> ans;
    if(!root)
        return ans;

    // map<col, map<row, multiset<val>>>
    // - Outer map sorts columns from left to right.
    // - Inner map sorts rows from top to bottom.
    // - multiset sorts duplicate (col, row) coordinates by node value.
    map<int, map<int, multiset<int>>> nodes;

    // queue stores: {node, {col, row}}
    queue<pair<Node *, pair<int, int>>> q;
    q.push({root, {0, 0}});

    while(!q.empty()) {
        auto front = q.front();
        q.pop();

        Node *currNode = front.first;
        int col = front.second.first;
        int row = front.second.second;

        nodes[col][row].insert(currNode->data);

        if(currNode->left) {
            q.push({currNode->left, {col - 1, row + 1}});
        }
        if(currNode->right) {
            q.push({currNode->right, {col + 1, row + 1}});
        }
    }

    // Flatten the map into the final result
    for(auto &colEntry : nodes) {
        vector<int> columnElements;
        for(auto &rowEntry : colEntry.second) {
            // rowEntry.second is a multiset<int>
            columnElements.insert(columnElements.end(),
                                  rowEntry.second.begin(),
                                  rowEntry.second.end());
        }
        ans.push_back(columnElements);
    }

    return ans;
}

int main() {

    Node *root = NULL;
    root = buildTree(root); // 1 2 4 -1 -1 5 -1 -1 3 6 -1 8 -1 -1 7 -1 9 -1 -1

    levelOrderIteratively(root);
    cout << endl;

    vector<int> ans = verticalOrder(root);
    cout << "vertical order: ";
    for(auto i : ans)
        cout << i << " ";
    cout << endl;

    return 0;
}