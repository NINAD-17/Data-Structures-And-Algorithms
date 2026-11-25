#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// MAX RECTANGLE IN BINARY MATRIX WITH ALL 1's
// time complexity: O(n * m)
// space complexity: O(m)

vector<int> nextSmallerElementIndex(vector<int> &heights, int size) {
    vector<int> next(size);
    stack<int> st;
    st.push(-1);

    for(int i = size - 1; i >= 0; i--) {
        while(st.top() != -1 && heights[st.top()] >= heights[i])
            st.pop();

        next[i] = st.top();
        st.push(i);
    }

    return next;
}

vector<int> prevSmallerElementIndex(vector<int> &heights, int size) {
    vector<int> prev(size);
    stack<int> st;
    st.push(-1);

    for(int i = 0; i < size; i++) {
        while(st.top() != -1 && heights[st.top()] >= heights[i])
            st.pop();

        prev[i] = st.top();
        st.push(i);
    }

    return prev;
}

// Changed parameter from vector<char>& to vector<int>&
int largestRectangleArea(vector<int> &heights) {
    int size = heights.size();

    vector<int> next = nextSmallerElementIndex(heights, size);
    vector<int> prev = prevSmallerElementIndex(heights, size);

    int area = 0;

    for(int i = 0; i < size; i++) {
        if(next[i] == -1)
            next[i] = size;

        int length = heights[i];
        int breadth = next[i] - prev[i] - 1;

        area = max(area, length * breadth);
    }

    return area;
}

int maximalRectangle(vector<vector<char>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    // Track column heights in a clean int vector (prevents char overflow & preserves input)
    vector<int> heights(m, 0);
    int maxArea = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            // Compare against character '1', not integer 0
            if(matrix[i][j] == '1')
                heights[j] += 1;
            else
                heights[j] = 0;
        }

        maxArea = max(maxArea, largestRectangleArea(heights));
    }

    return maxArea;
}

int main() {

    vector<vector<char>> binMatrix = {{'0', '1', '1', '0'}, {'1', '1', '1', '1'}, {'1', '1', '1', '1'}, {'1', '1', '0', '0'}};

    cout << "maximum area of rectangle in binary matrix is " << maximalRectangle(binMatrix) << endl;

    return 0;
}