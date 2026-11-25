#include <iostream>
using namespace std;

class Heap {
    public: 
        int arr[100];
        int size;

        // constructor
        Heap() {
            arr[0] = -1;
            size = 0;
        }

        // time complexity: O(log n)
        void insert(int val) {
            // add the new node at the end of array
            size = size + 1;
            int index = size;
            arr[index] = val;

            // swap that node until it gets its right position
            while(index > 1) {
                int parent = index / 2;
                if(arr[index] > arr[parent]) {
                    swap(arr[index], arr[parent]);
                    index = parent;
                } else {
                    return ;
                }
            }
        }

        void delete_first_node() {
            if(size == 0) {
                cout << "nothing to delete ^^" << endl;
                return;
            }

            // step 1: swap first node with last node
            arr[1] = arr[size]; // swap operation will take time so we can just add last element in arr[1] without swapping.
            
            // step 2: remove last node
            size--;

            // step 3: propagate root node to its correct position
            int i = 1;
            while(i <= size / 2) { // stop before leaf nodes
                int leftChildIndex = 2 * i;
                int rightChildIndex = 2 * i + 1;
                int largest = i;

                // Check if left child exists and is strictly greater
                if(leftChildIndex <= size && arr[leftChildIndex] > arr[largest])
                    largest = leftChildIndex;

                // Check if right child exists and is strictly greater than current largest
                if(rightChildIndex <= size && arr[rightChildIndex] > arr[largest])
                    largest = rightChildIndex;

                // If a child is larger, swap and descend; otherwise, heap property is satisfied
                if(largest != i) {
                    swap(arr[i], arr[largest]);
                    i = largest;
                } else { 
                    return ; // already in correct position
                }
            }
        }

        void print() {
            cout << "printing heap: ";
            for(int i = 1; i <= size; i++)
                cout << arr[i] << " ";
            cout << endl;
        }
};

int main() {

    Heap h;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);

    h.print();

    h.delete_first_node();
    h.print();

    h.delete_first_node();
    h.print();
    
    return 0;
}