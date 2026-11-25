#include <iostream>
using namespace std;

// HEAPIFY
// Time Complexity: O(n) [not O(n log n) - read why? from the notes in README.md]
// Space Complexity: O(h) or O(log n)

// 1. build max heap
void heapify(int *arr, int size, int index) {
    int largestElement = index;
    int leftChildIndex = 2 * index;
    int rightChildIndex = 2 * index + 1;
    cout << "lar: " << arr[largestElement] << " | left: " << arr[leftChildIndex] << " | right: " << arr[rightChildIndex] << endl;

    // if the index starts from 0 then `leftChildIndex <= size` should be only `<` and not `<=`
    if(leftChildIndex <= size && arr[largestElement] < arr[leftChildIndex]) {
        cout << "left large: " << arr[leftChildIndex] << endl;
        largestElement = leftChildIndex;
    }

    if(rightChildIndex <= size && arr[largestElement] < arr[rightChildIndex]) {
        cout << "right large: " << arr[rightChildIndex] << endl;
        largestElement = rightChildIndex;
    }

    //
    if(largestElement != index) {
        swap(arr[largestElement], arr[index]);
        cout << "swapped \n now, call for large: " <<  arr[largestElement] << " | at index: " << largestElement << endl << endl;
        heapify(arr, size, largestElement);
    }
}

// 2. build min heap
void heapify_minHeap(int *arr, int size, int index) {
    int smallestElement = index;
    int leftChildIndex = 2 * index;
    int rightChildIndex = 2 * index + 1;

    if(leftChildIndex <= size && arr[smallestElement] > arr[leftChildIndex]) {
        smallestElement = leftChildIndex;
    }

    if(rightChildIndex <= size && arr[smallestElement] > arr[rightChildIndex]) {
        smallestElement = rightChildIndex;
    }

    if(smallestElement != index) {
        swap(arr[smallestElement], arr[index]);
        heapify_minHeap(arr, size, smallestElement);
    }
}

void printArr(int *arr, int n) {
    for(int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {

    int arr[6] = {-1, 9, 3, 2, 6, 7}; //-1, 54, 53, 55, 52, 50 // -1, 55, 53, 56, 52, 54
    int size = 5;

    cout << "printing array before heapify: ";
    printArr(arr, size);

    // Heapify
    for(int i = size/2; i > 0; i--) {
        heapify(arr, size, i);
    }

    cout << "printing the array after heapify: ";
    printArr(arr, size);

    return 0;
}