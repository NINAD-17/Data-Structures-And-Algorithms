#include <iostream>
using namespace std;

class Node {
    public:
        int data; // data in that node
        Node* next; // pointer of node typel

        // constructor
        Node(int data) {
            this -> data = data;
            this -> next = NULL;
        }

        // destructor
        ~Node() {
            int data = this -> data;
            // memory free
            if(this -> next != NULL) {
                delete next;
                this -> next = NULL;
            }
            cout << "memory freed for node with data " << data << endl;
        }
};

void createNewLL(Node* &tail, int data) {
    cout << "create new linked list called" << endl;
    // allocate memory in heap for new node
    Node* newNode = new Node(data);

    // set tail point to newNode
    tail = newNode;

    // make it circular
    newNode -> next = newNode;
}

// element is a node after which we need to add new node with data
void insertNode(Node* &tail, int element, int data) {
    // if linkedlist isn't exist
    if(tail == NULL) {
        createNewLL(tail, data);
        return ;
    }

    // allocate memory in heap for new node
    Node* newNode = new Node(data);

    // add new node to existing linked list after a particular element
    Node* tempNode = tail -> next;
    while(tempNode -> data != element) {
        if(tempNode == tail)
            break;
        tempNode = tempNode -> next;
    }

    if(tempNode == tail && tempNode -> data != element) {
        cout << "element not found in linked list :(" << endl;
        return;
    }

    if(tempNode == tail && tempNode -> data == element)
        tail = newNode;

    newNode -> next = tempNode -> next;
    tempNode -> next = newNode;
}

void deleteNode(Node* &tail, int nodeToDelete) {
    // if linked list isn't exist
    if(tail == NULL) {
        cout << "linked list isn't exist!" << endl;
        return;
    }

    // only one node exist
    if(tail -> next == tail && tail -> data == nodeToDelete) {
        tail -> next = NULL;
        delete tail;
        tail = NULL;
        return;
    }

    Node* prev = tail;
    Node* curr = tail -> next;

    while(curr -> data != nodeToDelete) {
        if(curr == tail)
            break;
        prev = curr;
        curr = curr -> next;
    }

    if(curr -> data != nodeToDelete && curr == tail) {
        cout << "--- please enter a valid node to delete ---" << endl;
        return;
    }

    if(curr == tail) 
        tail = curr -> next; // WRONG: make prev the new tail i.e. tail = prev;

    prev -> next = curr -> next;
    curr -> next = NULL;
    delete curr;
}

void printLL(Node* &tail) {
    Node* temp = tail;

    if(tail == NULL) {
        cout << "linked list is empty or not exist :(" << endl;
        cout << "tail node: " << tail << endl << endl;
        return;
    }

    cout << "\nprinting LL: ";
    do {
        cout << temp -> data << " -> ";
        temp = temp -> next;
    } while (temp != tail);

    cout << "NULL" << endl;
}

int main() {

    Node* tail = NULL;

    insertNode(tail, 4, 10);
    printLL(tail);

    insertNode(tail, 10, 20);
    printLL(tail);

    insertNode(tail, 11, 30);
    printLL(tail);

    deleteNode(tail, 20);
    printLL(tail);

    deleteNode(tail, 17);
    printLL(tail);

    deleteNode(tail, 10);
    printLL(tail);

    cout << "tail: " << tail -> data << " (it's in front because printLL function is execute from tail node)" << endl;
    return 0;
}