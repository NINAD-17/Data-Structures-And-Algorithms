#include <iostream>
#include <stack>
using namespace std;

bool checkValidity(string &str) {
    // create stack to store opening parenthesis
    stack<char> st;

    for(int i = 0; i < str.length(); i++) {
        // if char is opening parenthesis then store it in stack
        if(str[i] == '{' || str[i] == '(' || str[i] == '[' || str[i] == '<') {
            st.push(str[i]);
            continue;
        }
        
        // if char is closing parenthesis then compare it with top of stack's element if it has corresponding opening parenthesis then pop that element from stack
        if(str[i] == '}' || str[i] == ')' || str[i] == ']' || str[i] == '>') {
            if(st.empty())
                return false; // if stack doesn't contain any opening bracket and closing bracket came as input
            else if(st.top() == '{' && str[i] == '}')
                st.pop();
            else if(st.top() == '(' && str[i] == ')')
                st.pop();
            else if(st.top() == '[' && str[i] == ']')
                st.pop();
            else if(st.top() == '<' && str[i] == '>')
                st.pop();
            else 
                return false; // not valid

            /*  update: below logic will not verify ({)} this condition. This is valid by below logic so don't use it.
                note: instead of above else if logic you can simply write below code after first if statement*/
            /*       you don't need to compare each bracket because we've defined 4 brackets and we only need to check there's opening bracket and it can be anything among 4 brackets */
            // else if(st.top() == '{' || st.top() == '(' || st.top() == '[' || st.top() == '<')
            //     st.pop();
            // else
            //     return false;
        
        }
    }

    // if any opening parenthesis don't get corresponding closing parenthesis
    if(st.empty()) 
        return true;
    else 
        return false;
}