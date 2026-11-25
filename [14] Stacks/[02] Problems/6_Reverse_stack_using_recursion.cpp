#include <iostream>
#include <stack>
#include "../lib/print.cpp"
using namespace std;

// REVERSE STACK USING RECURSION
// time complexity: O(n^2) because we're first making recursive calls till stack isn't empty and inside this function we're calling insertAtBottom which is again recursively calling till stack is not empty
// space complexity: O(n)  In the worst-case scenario, depth of the recursive call stack is n for reverseStack and n for insertAtBottom, leading to a total space complexity of O(n).

void insertAtBottom(stack<int> &st, int element) {
    // base case
    if(st.empty()) {
        st.push(element);
        return;
    }

    int currElement = st.top();
    st.pop();

    insertAtBottom(st, element);
    st.push(currElement);
}

void reverseStack(stack<int> &st) {
    // base case
    if(st.empty()) {
        return;
    }

    int currElement = st.top();
    st.pop();

    reverseStack(st);
    insertAtBottom(st, currElement);
}

// Iterative approach
// Time: O(n)
// Space: O(n)
stack<int> reverseStack_2(stack<int> &st) {
    stack<int> tempSt;

    while(!st.empty()) {
        int top = st.top();
        tempSt.push(top);
        st.pop();
    }

    return tempSt;
}

// OR using array
void reverseStack_2_arr(stack<int> &st) {
    int sizeOfStack = st.size();
    int *tempArr = new int[sizeOfStack];

    int i = 0;
    while(!st.empty()) {
        tempArr[i++] = st.top();
        st.pop();
    }

    for(int i = 0; i < sizeOfStack; i++) {
        st.push(tempArr[i]);
    }

    delete []tempArr;
    // return st; // manipulated original array so no need to return;
}

int main() {

    stack<int> st;

    st.push(7);
    st.push(1);
    st.push(4);
    st.push(5);
    st.push(6);
    printStack(st);

    // Reverse Stack using extra stack (iterative method)
    stack<int> tempSt = reverseStack_2(st);
    printStack(tempSt);

    st.push(7);
    st.push(1);
    st.push(4);
    st.push(5);
    st.push(6);

    // Iterative approach 2 using array
    reverseStack_2_arr(st);
    printStack(st);

    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.push(7);
    st.push(1);
    st.push(4);
    st.push(5);
    st.push(6);

    // Recursive approach
    reverseStack(st);
    printStack(st);

    return 0;
}