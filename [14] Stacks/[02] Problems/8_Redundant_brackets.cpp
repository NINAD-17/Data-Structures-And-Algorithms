#include <iostream>
#include <stack>
#include "../lib/valid_parenthesis.cpp"
#include "../lib/print.cpp"
using namespace std;

// REDUNDANT BRACKETS
// time complexity: O(n)
// space complexity: O(n)

// note: we're assuming that the input string contains valid parenthesis.
bool findRedundantBrackets(string &str) {
    // stack to store opening bracket and operators
    stack<char> st;

    for(int i = 0; i < str.length(); i++) {
        char ch = str[i];

        // if char is opening bracket or operator then push that in stack st
        if(ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            st.push(ch);
        } else {
            // if char is closing bracket
            if(ch == ')') {
                bool isRedundant = true;

                while(st.top() != '(') {
                    char top = st.top();
                    if(top == '+' || top == '-' || top == '*' || top == '/') {
                        isRedundant = false;
                    }
                    st.pop();
                }

                if(isRedundant) 
                    return true;
                st.pop(); // pop the opening bracket
            }
        }
    }

    return false;
}

// ---- my code ----
bool findRedundantBrackets_2(string &str) {
    // check the brackets are valid or not (in valid order)
    if(!checkValidity(str)) {
        cout << "Input string contains invalid brackets. So no need to find redundant brackets." << endl;
        return false; // not valid
    }

    stack<char> st;

    for(int i = 0; i < str.length(); i++) {
        char ch = str[i];
        
        if(ch == '(' || ch == '{' || ch == '[' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            st.push(ch);
            printCharStack(st);
        } else if(ch == ')' || ch == '}' || ch == ']') {
            bool isRedundant = true;

            while(!st.empty() && st.top() != '(' && st.top() != '{' && st.top() != '[') {
                char top = st.top();
                if(top == '+' || top == '-' || top == '*' || top == '/') {
                    isRedundant = false;
                }
                st.pop();
            }

            if(isRedundant)
                return true;

            if(!st.empty())
                st.pop(); // pop the opening bracket
        }
    }
    return false;
}

int main() {

    string str = "(a+b-(i*i))";
    // Examples to try
    //      1. Redundant Brackets: (a+b-(i*i)())
    //      2. Invalid Brackets: (a+b-(i*i)))
    //      3. Valid and Non-redundant Brackets: (a+b-(i*i))

    if(findRedundantBrackets_2(str))
        cout << str << " contains redundant brackets" << endl;
    else 
        cout << str << " doesn't contain redundant brackets" << endl;

    return 0;
}