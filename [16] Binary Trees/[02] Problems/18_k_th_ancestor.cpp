#include <iostream>
#include <climits>
#include "../lib/build.cpp"
using namespace std;

// K'th ANCESTOR

// Optimized Solution: Enhanced version of below good solution
Node* solve_2(Node* root, int &k, int node) {
    if (root == NULL)
        return NULL;
    
    if (root->data == node)
        return root;

    Node* leftAns = solve(root->left, k, node);

    // If leftAns is NOT NULL, the target node was already found on the left.
    // Do NOT explore root->right at all!
    Node* rightAns = NULL;
    if (leftAns == NULL) {
        rightAns = solve(root->right, k, node);
    }

    // Combine both symmetric cases (leftAns != NULL || rightAns != NULL)
    Node* found = (leftAns != NULL) ? leftAns : rightAns;
    if (found != NULL) {
        k--;
        if (k == 0) {
            k = INT_MAX; // Lock the answer so ancestors higher up don't overwrite it
            return root;
        }
        return found;
    }

    return NULL;
}

// time complexity: O(n)
// space complexity: O(h)

// good solution
Node* solve(Node* root, int &k, int node) {
    // base case
    if(root == NULL)
        return NULL;
    
    if(root -> data == node)
        return root;

    Node* leftAns = solve(root -> left, k, node);
    Node* rightAns = solve(root -> right, k, node);

    if(leftAns != NULL && rightAns == NULL) {
        k--; // decrement k each time so we can get ancestor
        if(k <= 0) { // after we get k-th ancestor if there're other ancestors present above then they can be overwrite because k == 0.
            k = INT_MAX; // that's why we've used k = INT_MAX so that it can't reach to 0 and our original ans will return everytime.
            return root; // return root element present at k = 0.
        }
        return leftAns; // it means leftAns node is the node to find.
    }

    if(leftAns == NULL && rightAns != NULL) {
        k--;
        if(k <= 0) {
            k = INT_MAX;
            return root;
        } 
        return rightAns;
    }

    return NULL; // if both the leftAns and rightAns are NULL then return NULL, means we don't get the node
}

int kthAncestor(Node* root, int k, int node) {
    if(root == NULL)
        return -1;

    Node* ans = solve(root, k, node);
    if(ans == NULL || ans -> data == node) // if the ans is NULL or it's giving answer same as node means it's a 1st node so it has no ancestor.
        return -1;
    else
        return ans -> data;
}


// written by me but unoptimized
void storeAncestors(Node* root, Node* n1, vector<int> &path) {
    if(root == NULL)
        return ;

    path.push_back(root -> data);

    for(auto i: path)
        cout << i << " ";
    cout << endl << endl;

    storeAncestors(root -> left, n1, path);
    storeAncestors(root -> right, n1, path);

    if(root -> data == n1 -> data) {
        cout << "\nfound at " << root -> data << endl;
        path.push_back(root -> data);
        cout << "found path: ";
        for(auto i: path)
            cout << i << " ";
        cout << endl << endl;
        return;
    }

    path.pop_back();
}

int find_kth_ancestor(Node* root, Node* n1, int k) {
    if(root == NULL)
        return -1;

    vector<int> path;
    storeAncestors(root, n1, path);

    if(path.empty())
        return -1; // node n1 not found

    if(k > path.size())
        return -2; // kth ancestor doesn't exist

    cout << endl;
    for(auto i: path)
        cout << i << " ";
    cout << endl;

    return path[path.size() - k];
}

int main() {
    Node* root = NULL;
    root = buildTree(root);
    levelOrderIteratively(root);

    int k = 1;
    Node* n1 = new Node(4);

    int ans = find_kth_ancestor(root, n1, k);
    if(ans >= 0) 
        cout << k << "th ancestor of node " << n1 -> data << " is " << ans << endl;
    else if(ans == -1)
        cout << "node " << n1 << " not found" << endl;
    else if(ans == -2)
        cout << "kth ancestor not found" << endl;

    return 0;
}