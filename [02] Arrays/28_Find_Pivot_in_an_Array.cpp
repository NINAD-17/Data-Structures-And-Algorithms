#include <iostream>
using namespace std;

// time complexity: O(log(n))

// Pivot: Smallest Element
int findPivot_smaller(int *arr, int n) {
    if(arr[0] <= arr[n - 1]) // Meaning: 1 2 3 4 5 6 7 is already sorted. No rotation happened.
        return 0;            // smallest element is already at index 0

    int st = 0, en = n - 1;

    while(st < en) {
        int mid = st + (en - st) / 2;
        if(arr[mid] >= arr[0])
            st = mid + 1;
        else
            en = mid;
    }

    return st;
}

// Pivot: Greatest Element
int findPivot_greater(int *arr, int n) {
    if(n == 1 || arr[0] < arr[n - 1])
        return n - 1; // Not rotated

    int st = 0, en = n - 1;

    while(st < en) {
        // Bias mid towards right so (mid - 1) is safe and we don't get stuck
        int mid = st + (en - st + 1) / 2;

        if(arr[mid] >= arr[0]) {
            // mid is in the first sorted segment, peak is at mid or to the right
            st = mid;
        } else {
            // mid is in the second sorted segment, peak must be strictly to the left
            en = mid - 1;
        }
    }

    return st;
}

int findPivot_greater_2(int *arr, int n) {
    int minIndex = findPivot_smaller(arr, n);
    return (minIndex - 1 + n) % n;
}

int main() {
    int arr[10], size;

    cout << "Enter size of array(less than 10): ";
    cin >> size;

    cout << "Enter " << size << " number of elements: ";
    for(int i = 0; i < size; i++)
        cin >> arr[i];

    cout << "Pivot (If we consider smallest number as a pivot) is " << findPivot_smaller(arr, size) << endl;
    cout << "Pivot (If we consider smallest number as a pivot) is " << findPivot_greater(arr, size) << endl;

    return 0;
}