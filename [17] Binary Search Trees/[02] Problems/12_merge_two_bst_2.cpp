#include <bits/stdc++.h>
#include "../lib/build.cpp"
using namespace std;

// MERGE TWO BSTs IN-PLACE (Using Sorted Doubly Linked List)
// Time Complexity:  O(M + N)
// Space Complexity: O(H1 + H2)  [Recursion stack only, zero extra arrays]

// Step 1: Convert BST into Sorted Doubly Linked List (in-place)
// Uses right pointer as 'next' and left pointer as 'prev'
void convertIntoSortedDLL(Node* root, Node* &head) {
    // Base Case
    if(root == NULL)
        return ;

    // Right
    convertIntoSortedDLL(root -> right, head);

    // Node: attach current root before 'head'
    root -> right = head;
    if(head != NULL)
        head -> left = root;
    
    head = root;

    // Left
    convertIntoSortedDLL(root -> left, head);
}

// Step 2: Merge two sorted Doubly Linked Lists
Node* mergeLinkedList(Node* head1, Node* head2) {
    Node* head = NULL;
    Node* tail = NULL;

    while(head1 != NULL && head2 != NULL) {
        if(head1 -> data < head2 -> data) {
            if(head == NULL) {
                head = head1;
                tail = head1;
                head1 = head1 -> right;
            } else {
                tail -> right = head1;
                head1 -> left = tail;
                tail = head1;
                head1 = head1 -> right;
            }
        } else {
            if(head == NULL) {
                head = head2;
                tail = head2;
                head2 = head2 -> right;
            } else {
                tail -> right = head2;
                head2 -> left = tail;
                tail = head2;
                head2 = head2 -> right;
            }
        }
    }

    while(head1 != NULL) {
        tail -> right = head1;
        head1 -> left = tail;
        tail = head1;
        head1 = head1 -> right;
    }

    while(head2 != NULL) {
        tail -> right = head2;
        head2 -> left = tail;
        tail = head2;
        head2 = head2 -> right;
    }

    return head;
}

// Helper: Count total nodes in the merged Doubly Linked List
int countNodes(Node* head) {
    int cnt = 0;
    Node* temp = head;
    while(temp != NULL) {
        cnt++;
        temp = temp -> right;
    }
    return cnt;
}

// Step 3: Convert Sorted Doubly Linked List into Balanced BST in O(N) time
Node* sortedLLToBST(Node* &head, int n) {
    // Base Case
    if(n <= 0 || head == NULL)
        return NULL;

    // Build Left Subtree from first n/2 nodes
    Node* leftSubtree = sortedLLToBST(head, n / 2);

    // Current 'head' is now pointing to the middle element -> make it root
    Node* root = head;
    root -> left = leftSubtree;

    // Move head pointer forward for the right subtree
    head = head -> right;

    // Build Right Subtree from remaining (n - n/2 - 1) nodes
    root -> right = sortedLLToBST(head, n - n / 2 - 1);

    return root;
}

Node* mergeBST(Node* root1, Node* root2) {
    // Step 1: Convert both BSTs into Sorted Doubly Linked Lists in-place
    Node* head1 = NULL;
    convertIntoSortedDLL(root1, head1);
    if(head1 != NULL) head1 -> left = NULL;

    Node* head2 = NULL;
    convertIntoSortedDLL(root2, head2);
    if(head2 != NULL) head2 -> left = NULL;

    // Step 2: Merge two sorted Doubly Linked Lists
    Node* mergedHead = mergeLinkedList(head1, head2);

    // Step 3: Convert Sorted Doubly Linked List into Balanced BST
    int totalNodes = countNodes(mergedHead);
    return sortedLLToBST(mergedHead, totalNodes);
}

void inorderTraversal(Node* root) {
    if(root == NULL) return ;

    inorderTraversal(root -> left);
    cout << root -> data << " ";
    inorderTraversal(root -> right);
}

int main() {
    // Hardcoded BST 1:
    //       10
    //      /  \
    //     5    20
    //    / \
    //   2   7
    Node* root1 = new Node(10);
    root1 -> left = new Node(5);
    root1 -> right = new Node(20);
    root1 -> left -> left = new Node(2);
    root1 -> left -> right = new Node(7);

    // Hardcoded BST 2:
    //       15
    //      /  \
    //     12   25
    //    /    /
    //   11   18
    Node* root2 = new Node(15);
    root2 -> left = new Node(12);
    root2 -> right = new Node(25);
    root2 -> left -> left = new Node(11);
    root2 -> right -> left = new Node(18);

    Node* mergedRoot = mergeBST(root1, root2);

    cout << "Merged Balanced BST (Level Order):" << endl;
    levelOrderIteratively(mergedRoot);

    cout << "\nInorder Traversal (Sorted Check): ";
    inorderTraversal(mergedRoot);
    cout << endl;

    return 0;
}