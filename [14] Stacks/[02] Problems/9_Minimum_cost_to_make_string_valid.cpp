#include <iostream>
#include <stack>
using namespace std;

// Instructions:
//      - No. of open braces = No. of close braces
//      - Every close brace should have open brace before it
// Examples: 
//      - Input string will contain only two char '{' and '}'
//      - Valid strings: {}{} or {{}} or {{}{}}
//      - Invalid strings: }{} or {}}{{}
// Find out minimum how much brackets should be reverse to make expression valid.
// Ex - str = "{{{}" => "{}{}" reversed str[1] means only one bracket

// Invalid String patterns (by ignoring valid part from the string):
//      1. {{{{.... (only open)
//      2. }}}}.... (only close)
//      3. }}}}{{{{... (first open then close)
// Note: If number of braces are in odd number then it's obvious that it has invalid string pattern

// Some examples: (after removing valid pattenrs '{}')
// consider 'a' as closing brace ')' and 'b' as opening brace '('
//      1. {{{{   - here b = 4.           We can see that 2 braces at index [1, 3] needs to change to '}' (to form valid pattern) i.e b/2 = 2
//      2. }}}}   - here a = 4.           We can see that 2 braces at index [0, 2] needs to change to '{'                         i.e a/2 = 2
//      3. }}}{{{ - here a = 3 and b = 3. We can see that 3 braces at index [0, 2, 3, 5] needs to change to '}'
//      4. }}}}{{{{ - here a = 4, b = 4.  We can see that here 4 braces at index [0, 2, 5, 7] needs to change.
// To satisfy all condition and get accurate number of braces needs to change we use below formula,
//      ans = (a + 1)/2 + (b + 1)/2

int findMinimumCost(string &str) {
    // odd condition - Invalid pattern
    if(str.length() % 2 != 0)
        return -1;

    // remove valid part
    stack<char> st;
    for(int i = 0; i < str.length(); i++) {
        char ch = str[i];
        
        if(ch == '{') {
            st.push(ch);
        } else {
            // ch is a closed brace ')'
            if(!st.empty() && st.top() == '{') {
                st.pop();
            } else {
                st.push(ch);
            }
        }
    }

    // now the stack contains invalid expressions
        int a = 0;
        int b = 0;
        while(!st.empty()) {
            if(st.top() == '{') {
                b++;
            } else {
                a++;
            }
            st.pop();
        }

        cout << "Total number of { is " << b << endl;
        cout << "Total number of } is " << a << endl;

        int ans = (a + 1)/2 + (b + 1)/2;
        return ans;
}

// Without Using Stack (Optimized)
// Time: O(n)
// Space: O(1)
int findMinimumCost2(string &str) {
    if(str.length() % 2 != 0)
        return -1;

    int open = 0;  // Unmatched '{' (previously 'b')
    int close = 0; // Unmatched '}' (previously 'a')

    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '{') {
            open++;
        } else {
            // If there is an unmatched '{' waiting, pair it up!
            if(open > 0)
                open--;
            else // No '{' available to match this '}'
                close++;
        }
    }

    return (open + 1) / 2 + (close + 1) / 2;
}


int main() {
    string str = "}}{}}}{}{{"; // {}{}{}{}{}

    int minCost = findMinimumCost(str);
    if(minCost == -1) {
        cout << "Contain odd number of braces which can't be corrected." << endl;
    } else {
        cout << "Minimum cost to make valid string is " << minCost << endl;
    }

    return 0;
}