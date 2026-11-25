#include <bits/stdc++.h>
#include "../../[13] Linked List/lib/singly_linkedlist.cpp"
using namespace std;

// MERGE K SORTED LINKED LISTS
// don't make new linkedlist only change pointers

// time complexity: O(n*k log k)
// space complexity: O(k)

class compare {
    public: 
        bool operator() (Node* a, Node* b) {
            return a -> data > b -> data;
        }
};

Node* mergeKLists(vector<Node*> &lists) {
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    int k = lists.size();

    if(k == 0) return NULL;

    // step 1: 
    for(int i = 0; i < k; i++) {
        if(lists[i] != NULL) { 
            minHeap.push(lists[i]); // insert 1st node of each linked list in minHeap
        }
    }

    Node* head = NULL;
    Node* tail = NULL;

    // step 2: 
    while(!minHeap.empty()) {
        Node* top = minHeap.top();
        minHeap.pop();

        if(top -> next != NULL) 
            minHeap.push(top -> next);

        if(head == NULL) { // answer is empty
            head = top;
            tail = top;
        } else { // insert at linked list
            tail -> next = top;
            tail = top;
        }
    }

    return head;
}

// brute force
// time complexity: O(n*k log(n*k))
// space complexity: O(n * k)
Node* mergeLL(vector<Node*> lists) {
    vector<int> ans;

    for(int i = 0; i < lists.size(); i++) {
        Node* currNode = lists[i];
        while(currNode != NULL) {
            ans.push_back(currNode -> data);
            currNode = currNode -> next;

            // if(currNode -> next == NULL && i != lists.size() - 1) {
            //     currNode -> next = lists[i + 1];
            // }
        }
    }

    sort(ans.begin(), ans.end());
    for(auto i: ans)
        cout << i << " ";
    cout << endl;

    for(int i = 0; i < lists.size() - 1; i++) {
        Node* curr = lists[i];
        while(curr -> next != NULL) {
            curr = curr -> next;
        }
        curr -> next = lists[i + 1]; 
    }

    Node* currNode = lists[0]; // pointer of 1st list which is connected to rest list
    for(int i = 0; i < ans.size(); i++) {
        currNode -> data = ans[i];
        currNode = currNode -> next;
    }

    return lists[0];
}

int main() {

    Node* head1 = NULL;
    Node* tail1 = NULL;
    insertAtHead(head1, tail1, 1);
    insertAtHead(head1, tail1, 10);
    insertAtHead(head1, tail1, 20);

    Node *head2 = NULL;
    Node *tail2 = NULL;
    insertAtHead(head2, tail2, 5);
    insertAtHead(head2, tail2, 15);
    insertAtHead(head2, tail2, 19);

    Node *head3 = NULL;
    Node *tail3 = NULL;
    insertAtHead(head3, tail3, 3);
    insertAtHead(head3, tail3, 6);
    insertAtHead(head3, tail3, 12);

    printLL(head1);
    printLL(head2);
    printLL(head3);

    vector<Node*> lists = {head1, head2, head3};

    Node* ans = mergeLL(lists);
    printLL(ans);

    return 0;
}