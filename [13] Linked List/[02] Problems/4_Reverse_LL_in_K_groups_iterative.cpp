#include <iostream>
#include "../lib/singly_linkedlist.cpp"
using namespace std;

// REVERSE A LINKED LIST IN K GROUPS (Iterative)
// time complexity: O(n)
// space complexity: O(1)

// ITERATIVE SOLUTION
Node* reverseKGroup(Node* &head, int k) {
    if(head == NULL || head -> next == NULL || k <= 1) return head;

    Node* dummy = new Node(0); // new head pointer
    dummy -> next = head;

    Node* prevTail = dummy;
    Node* curr = head;

    while(curr != NULL) {
        // check if there're k nodes left
        Node* check = curr;
        for(int i = 0; i < k; i++) {
            if(check == NULL) {
                // not enough nodes left -> connect leftover nodes  
                prevTail -> next = curr;
                return dummy -> next;
            }
            check = check -> next;
        }

        // reverse k nodes
        Node* prev = NULL;
        Node* temp = curr; // old head become tail
        for(int i = 0; i < k; i++) {
            Node* forward = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = forward;
        }

        // connect previous group to new head
        prevTail -> next = prev;
        prevTail = temp; // update tail for next iteration
    }
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;

    insertAtTail(head, tail, 3);
    insertAtTail(head, tail, 2);
    insertAtTail(head, tail, 7);
    insertAtTail(head, tail, 8);
    insertAtTail(head, tail, 9);
    insertAtTail(head, tail, 10);
    printLL(head);

    int k = 4; // k is number of group nodes
    head = reverseKGroup(head, k);
    printLL(head);

    return 0;
}