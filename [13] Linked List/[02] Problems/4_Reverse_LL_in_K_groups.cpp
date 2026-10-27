#include <iostream>
#include "../lib/singly_linkedlist.cpp"
using namespace std;

// REVERSE A LINKED LIST IN K GROUPS
// time complexity: O(n)
// space complexity: O(n)

// RECURSIVE SOLUTION
// -- (i) It reverses non-K nodes as well
Node* reverseLL(Node* &head, int k) {
    // empty linked list
    if(head == NULL) 
        return NULL;

    // more than one nodes are exist
    Node* prev = NULL;
    Node* curr = head;
    Node* forward = NULL;

    int numOfIterations = 1;
    while(curr != NULL && numOfIterations <= k) { // reversing k nodes
        forward = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = forward;
        numOfIterations++;
    }

    if(forward != NULL) 
        head -> next = reverseLL(forward, k); // recursion call // Ex - reversed LL in 1st k group is 3, 2, 7, 8, 9, 10 ==> 8, 7, 2, 3. Head is 3. So 3 -> next = recursive call ==> 8,7,2,3,10,9

    // update head pointer
    return prev;
}

// -- (ii) Stop non-K reversal
Node* reverseLL2(Node* &head, int k) {
    if(head == NULL) return NULL;

    // stop non-k reversal
    Node* check = head;
    for(int i = 0; i < k; i++) {
        if(check == NULL) return head;
        check = check -> next;
    }

    Node* prev = NULL;
    Node* curr = head;
    Node* forward = NULL;

    int numOfIterations = 1;
    while(curr != NULL && numOfIterations <= k) {
        forward = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = forward;
        numOfIterations++;
    }

    if(forward != NULL)
        head -> next = reverseLL2(curr, k);

    return prev;
}


/********************************************************* */
Node* reverseInKGroups(Node* &head, int k) {
    // if linkedlist is empty or only one node present
    if(head == NULL || head -> next == NULL)
        return head;

    // if less than k nodes are present in linked list
    int lenOfLL = getLengthOfLL(head);
    if(lenOfLL < k) {
        cout << "can't reverse in k group: num or nodes are less than k" << endl;
        return head;
    }
    
    // return reverseLL(head, k);
    return reverseLL2(head, k); // updated head node
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
    head = reverseInKGroups(head, k);
    printLL(head);

    return 0;
}