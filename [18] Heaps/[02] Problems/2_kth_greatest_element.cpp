#include <bits/stdc++.h>
using namespace std;

// KTH GREATEST ELEMENT
// Time: O(n log k)
// Space: O(k)

int kthGreatestElement(int *arr, int size, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;

    for(int i = 0; i < k; i++)
        minHeap.push(arr[i]);

    for(int i = k; i < size; i++) {
        if(arr[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(arr[i]);
        }
    }

    return minHeap.top();
}

int main() {

    int arr[5] = {7, 10, 4, 20, 15};
    int size = 5;
    int k = 3;

    cout << k << "th greatest element is " << kthGreatestElement(arr, size, k) << endl;
    return 0;
}