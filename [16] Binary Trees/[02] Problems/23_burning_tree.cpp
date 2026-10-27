#include <bits/stdc++.h>
#include "../lib/build.cpp"
using namespace std;

// Burning Tree

// Create mapping and return target node (step 1 and 2)
Node* createParentMapping(Node* root, int target, map<Node*, Node*> &nodeToParent) {
    Node* result = NULL;

    queue<Node*> q;
    q.push(root);

    // Mark parent of root as NULL
    nodeToParent[root] = NULL;

    while(!q.empty()) {
        Node* front = q.front();
        q.pop();

        if(front -> data == target) {
            result = front;
        }

        if(front -> left) {
            nodeToParent[front -> left] = front;
            q.push(front -> left);
        }

        if(front -> right) {
            nodeToParent[front -> right] = front;
            q.push(front -> right);
        }
    }

    return result; // targetNode
}

int burnTree(Node* root, map<Node*, Node*> nodeToParent) {
    map<Node*, bool> visited;
    queue<Node*> q;

    q.push(root);
    visited[root] = true;

    int ans = 0;
    
    while(!q.empty()) {
        bool flag = false;
        int size = q.size();

        for(int i = 0; i < size; i++) {
            Node* front = q.front();
            q.pop();

            // Check left child
            if(front -> left && !visited[front -> left]) {
                flag = true;
                q.push(front -> left);
                visited[front -> left] = true;
            }

            // Check right child
            if(front -> right && !visited[front -> right]) {
                flag = true;
                q.push(front -> right);
                visited[front -> right] = true;
            }

            // Check parent node
            if(nodeToParent[front] && !visited[nodeToParent[front]]) {
                flag = true;
                q.push(nodeToParent[front]);
                visited[nodeToParent[front]] = true;
            }
        }
        
        if(flag == true) {
            ans++;
        }
    }

    return ans;
}

// Minimum time to burn tree
int minTime(Node* root, int target) {
    // Step 1: Create nodeToParent mapping
    // Step 2: Find target node
    map<Node*, Node*> nodeToParent;
    Node* targetNode = createParentMapping(root, target, nodeToParent);

    // Step 3: Burn the tree in min time
    int ans = burnTree(targetNode, nodeToParent);

    return ans;

}

int main() {
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);
    Node* node6 = new Node(6);
    Node* node7 = new Node(7);
    Node* node8 = new Node(8);
    Node* node9 = new Node(9);
    Node* node10 = new Node(10);

    node1 -> left = node2;
    node1 -> right = node3;

    node2 -> left = node4;
    node2 -> right = node5;

    node5 -> left = node7;
    node5 -> right = node8;

    node3 -> right = node6;
    
    node6 -> right = node9;

    node9 -> right = node10;

    Node* root = node1;
    levelOrderIteratively(root);

    cout << "Minimum time to burn tree is " << minTime(root, 8) << " seconds." << endl;

    return 0;
}