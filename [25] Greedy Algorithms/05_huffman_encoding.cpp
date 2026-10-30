#include <bits/stdc++.h>
using namespace std;

// Huffman Encoding

// Time: O(N log N)
// Space: O(N)

class Node {
    public:
        int data;
        Node* left;
        Node* right;

        Node(int data) {
            this -> data = data;
            left = nullptr;
            right = nullptr;
        }
};

class Comparator {
    public:
        bool operator()(Node* a, Node* b) {
            return a -> data > b -> data;
        }
};

void traverse(Node* root, vector<string> &ans, string temp) {
    if(root -> left == nullptr && root -> right == nullptr) {
        ans.push_back(temp);
        return;
    }

    traverse(root -> left, ans, temp + '0');
    traverse(root -> right, ans, temp + '1');
}

vector<string> huffmanEncoding(string s, vector<int> &freq) {
    priority_queue<Node*, vector<Node*>, Comparator> minHeap;

    for(int i = 0; i < freq.size(); i++) {
        Node* temp = new Node(freq[i]); 
        minHeap.push(temp);
    }

    while(minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node(left -> data + right -> data);
        newNode -> left = left;
        newNode -> right = right;
        
        minHeap.push(newNode);
    }

    Node* root = minHeap.top();
    vector<string> ans;
    string temp = "";

    traverse(root, ans, temp);
    return ans;
}

int main() {
    string s = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};



    return 0;
}