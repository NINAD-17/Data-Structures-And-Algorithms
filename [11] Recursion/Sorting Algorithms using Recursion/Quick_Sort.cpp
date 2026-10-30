#include <iostream>
#include <vector>
using namespace std;

// Quick Sort

// Approach 2: 3 Way Randomized Approach (using Dutch National Flag Algorithm)
void quickSort3Way(vector<int> &nums, int st, int en) {
    if(st >= en)
        return;

    // 1. Pick a random pivot to avoid O(N^2) worst-case on sorted arrays
    int randIdx = st + rand() % (en - st + 1);
    swap(nums[st], nums[randIdx]);
    int pivot = nums[st];

    // 2. Dutch National Flag (3-way partition)
    // [st ... lt-1]  < pivot
    // [lt ... gt]   == pivot
    // [gt+1 ... en]  > pivot
    int lt = st;
    int gt = en;
    int i = st + 1;

    while(i <= gt) {
        if(nums[i] < pivot) {
            swap(nums[lt++], nums[i++]);
        } else if(nums[i] > pivot) {
            swap(nums[i], nums[gt--]);
        } else {
            i++; // Equal to pivot: keep in middle
        }
    }

    // 3. Recurse only on the strictly smaller and strictly greater regions
    quickSort3Way(nums, st, lt - 1);
    quickSort3Way(nums, gt + 1, en);
}

// ------------------------------------------------------------------------
// Approach 1: ad-hoc Counting Based Partition approach
// Note: This algorithm has issues with duplicate elements. So prefer 3 way partitioning approach.

// Time complexity (best case): O(n log n)
// Space complexity (best case): O(log n)
// Read explaination of time and space complexity from README.md

int partition(int *arr, int st, int en) {

    // Decide pivot element
    int pivot = arr[st];

    // Count all the numbers which are less than pivot
    int count = 0;
    for(int i = st; i <= en; i++) {
        if(arr[i] < pivot)
            count++;
    }

    // Put pivot at right position
    int pivotIndex = st + count;
    swap(arr[pivotIndex], arr[st]);

    // Satisfy condition < and > than pivot in left and right parts ( ... < pivot < ...)
    int i = st, j = en;

    while(i < pivotIndex && j > pivotIndex) {
        while(arr[i] < pivot)
            i++;

        while(arr[j] >= pivot) // In counting we've used a[j] < pivot so all >= elements will be on right side. That's why we've used >= here.
            j--;

        if(i < pivotIndex && j > pivotIndex)
            swap(arr[i++], arr[j--]);
    }

    return pivotIndex;
}

void quick_sort(int *arr, int st, int en) {
    // Base Case
    if(st >= en)
        return;

    // Partition
    int pivotIndex = partition(arr, st, en);

    // Sort left part
    quick_sort(arr, st, pivotIndex - 1);

    // Sort right part
    quick_sort(arr, pivotIndex + 1, en);
}

int main() {
    // int arr[6] = {3, 5, 1, 8, 2, 4};
    // int size = 6;

    // quick_sort(arr, 0, size - 1);

    vector<int> arr = {3, 5, 1, 8, 2, 4};
    int size = 6;

    quickSort3Way(arr, 0, size - 1);

    // Output
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}