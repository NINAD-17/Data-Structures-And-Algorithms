#include <iostream>
using namespace std;

// In-place code: Without any extra space
void reverseArr(int *arr, int st, int en) {
    while(st < en)
        swap(arr[st++], arr[en--]);
}

// Detailed explaination is available on README.md
// Time: O(n)
// Space: O(1)
void rotateInPlace(int *arr, int n, int rotateBy) {
    if(n <= 1) return;

    rotateBy = (((rotateBy % n) + n) % n);

    if(rotateBy == 0) return;

    // * Right Rotation (rotate from right side)
    // 1. Reverse whole array
    reverseArr(arr, 0, n - 1);

    // 2. Reverse first k (rotateBy) elements
    reverseArr(arr, 0, rotateBy - 1);

    // 3. Reverse remaining n - k (rotateBy) elements
    reverseArr(arr, rotateBy, n - 1);
}

// Rotate to left by right rotation algorithm
void rotateToLeft(int *arr, int n, int rotateBy) {
    if(n <= 1)
        return ;

    // here, rotateBy factor is for left rotation
    rotateBy = (((rotateBy % n) + n) % n); // rotate to right by rotateBy factor
    rotateBy = (n - rotateBy) % n; // convert left rotation to equivalent right rotation

    if(rotateBy == 0)
        return ;

    // Apply right rotation
    reverseArr(arr, 0, n - 1);

    reverseArr(arr, 0, rotateBy - 1);

    reverseArr(arr, rotateBy, n - 1);
}

// ------------------------------------------------------------------------

// Time Complexity: O(n)
// auxillary space = O(1) but if we consider output space then it's O(n)
void rotateArr(int *arr, int n, int rotateBy, int *ans) {
    for(int i = 0; i < n; i++)
        ans[(i + rotateBy) % n] = arr[i]; // Formula
}

void printArr(int *arr, int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {

    int arr[10] = {1, 7, 9, 11}, ans[10];
    int n = 4, rotateBy = 2;

    cout << "Before Rotation: ";
    printArr(arr, n);

    rotateArr(arr, n, rotateBy, ans);

    cout << "After Rotation: ";
    printArr(ans, n);

    cout << endl << "Rotate Inplace" << endl;
    rotateBy = 2;
    rotateInPlace(arr, n, rotateBy);
    printArr(arr, n);

    cout << "Revert rotation using by taking rotateBy as negetive number (left rotation)" << endl;
    rotateBy = -2;
    rotateInPlace(arr, n, rotateBy);
    printArr(arr, n);

    return 0;
}