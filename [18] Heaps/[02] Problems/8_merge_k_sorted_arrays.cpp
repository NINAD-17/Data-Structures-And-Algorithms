#include <bits/stdc++.h>
using namespace std;

// MERGE K SORTED ARRAYS

// optimized approach
// time complexity: O(n*k log k)
// space complexity: 
    // Auxillary Space: O(k)
    // If include ans then O(n * k)

// create custom data structure
class node {
    public: 
        int data;
        int row; 
        int col;

        node(int data, int row, int col) {
            this -> data = data;
            this -> row = row;
            this -> col = col;
        }
};

class compare {
    public: 
        bool operator() (node* a, node* b) {
            return a -> data > b -> data;
        }
};

vector<int> mergeKSortedArrays(vector<vector<int>> &arrays, int k) {
    // create minHeap which sorts the minHeap on the basis of node's data property
    priority_queue<node*, vector<node*>, compare> minHeap;

    // step 1: insert 1st elements of k arrays in minHeap
    for(int i = 0; i < k; i++) {
        node* temp = new node(arrays[i][0], i, 0); // make a node by the data and row-col index
        minHeap.push(temp);
    }

    vector<int> ans;

    // step 2: 
    while(!minHeap.empty()) {
        node* temp = minHeap.top();

        ans.push_back(temp -> data);
        minHeap.pop();

        int row = temp -> row;
        int col = temp -> col;

        if(col + 1 < arrays[row].size()) {
            node* next = new node(arrays[row][col + 1], row, col + 1);
            minHeap.push(next);
        }
    }

    return ans;
}

// brute force: we ignored that each array from arrays is in sorted order
// time complexity: O(n*k log(n*k))
// space complexity: O(n * k) where k is the total number of arrays and n is the size of each array
vector<int> merge(vector<vector<int>> &arrays) {
    vector<int> ans;

    for(int i = 0; i < arrays.size(); i++) {
        for(int j = 0; j < arrays[i].size(); j++) {
            ans.push_back(arrays[i][j]);
        }
    }

    for(auto i: ans)
        cout << i << " ";
    cout << endl;

    sort(ans.begin(), ans.end());

    return ans;
}

int main() {

    vector<vector<int>> arrays = {{1, 10, 20}, {5, 15, 19}, {3, 6, 12}};

    vector<int> ans = merge(arrays);

    cout << "sorted array: ";
    for(auto i: ans)
        cout << i << " ";
    cout << endl;

    vector<int> ans2 = mergeKSortedArrays(arrays, arrays.size());
    cout << "sorted array (*optimized): ";
    for(auto i: ans)
        cout << i << " ";
    cout << endl;

    return 0;
}