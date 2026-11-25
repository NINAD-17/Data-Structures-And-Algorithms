#include <iostream>
#include <stack>
#include "../lib/valid_parenthesis.cpp"
#include "../lib/print.cpp"
using namespace std;

// Valid Mathematical Expression
// In Redundant Brackets problem, problem statement guarantees a syntactically valid mathematical expression (so malformed expressions like {+}, (), or a++b are never part of the test cases).
// But this problem asks to check if the input expression is valid or not.
// If in Redundant Brackets problem expression is {+} then also it'll return it as valid expression but actually it's not as + alone isn't valid mathematical expression. It should be like {a+b}. 
// To reject malformed expressions like {+}, (a+), or (+b), an operator (+, -, *, /) must always be sandwiched between two valid operands (a variable/digit on the left, and a variable/digit on the right).

bool isValidExpression(const string &str) {
    stack<char> brackets;
    bool expectedOperand = true; // Initially we need an operand or '('

    for(char ch: str) {
        if(ch == ' ') continue;

        if(ch == '(' || ch == '{' || ch == '[') {
            if(!expectedOperand) return false;
            
            brackets.push(ch);
            expectedOperand = true;
        }

        else if(ch == ')' || ch == '}' || ch == ']') {
            if(expectedOperand || brackets.empty()) return false;

            char top = brackets.top();
            if((ch == ')' && top != '(') ||
               (ch == '}' && top != '{') ||
               (ch == ']' && top != '[')) {
                return false;
            }

            brackets.pop();
            expectedOperand = false;
        }

        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if(expectedOperand) return false;
            expectedOperand = true;
        }

        else if(isalnum(ch)) {
            if(!expectedOperand) return false;
            expectedOperand = false;
        }
    }

    return brackets.empty() && !expectedOperand;
}

int main() {
    string str = "";

    if(isValidExpression(str))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    
    return 0;
}