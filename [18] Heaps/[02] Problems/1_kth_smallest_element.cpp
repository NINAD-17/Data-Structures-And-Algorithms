#include <iostream>
#include <queue>
using namespace std;

// K-TH SMALLEST ELEMENT
// Time: O(n log k)
// Space: O(k)

int kthSmallestElement(int *arr, int size, int k) {

    // step 1: make a priority queue for first k elements
    priority_queue<int> pq;

    for(int i = 0; i < k; i++)
        pq.push(arr[i]);

    // step 2: for remaining elements k to size - 1
    for(int i = k; i < size; i++) {
        if(arr[i] < pq.top()) {
            pq.pop(); // pop top max element from heap
            pq.push(arr[i]); // push smaller element
        }
    }

    // return k-th smallest element
    return pq.top();
}

int main() {
    int arr[5] = {7, 10, 4, 20, 15};
    int size = 5;
    int k = 4;

    cout << k << "th smallest element is " << kthSmallestElement(arr, size, k) << endl;
    return 0;
}