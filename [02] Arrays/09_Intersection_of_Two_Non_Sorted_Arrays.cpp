#include <iostream>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Using unordered list
// Time Complexity: O(n + m)
void intersectionOfTwoNonSortedArr_um(int *arr1, int n, int *arr2, int m, int *intersection) {
    unordered_map<int, int> mp;
    int k = 0;

    for(int i = 0; i < n; i++)
        mp[arr1[i]]++;

    for(int j = 0; j < m; j++) {
        if(mp.count(arr2[j]) && mp[arr2[j]] > 0) {
            intersection[k++] = arr2[j];
            mp[arr2[j]]--;
        }
    }
}

// Optimized Approach
// Time Complexity: O(n log(n) + m log(m))
// Space Complexity: O(1)
void intersectionOfTwoNonSortedArr1(int *arr1, int n, int *arr2, int m, int *intersection) {
    int i = 0, j = 0, k = 0;
    if(n == 0 || m == 0) {
        cout << "One array is empty!" << endl;
        return;
    }

    // we're solving this problem by approach of two sorted arrays
    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);

    int count = INT_MIN; // If you want only unique elements in intersection array
    while(i < n && j < m) {
        if(arr1[i] == arr2[j]) {
            if(count == arr1[i]) { // If there is another pair of intersections, it will not be added to the intersection array. As array is sorted.
                i++, j++;
                continue;
            }
            count = arr1[i];
            intersection[k++] = arr1[i];
            i++, j++;
        } else if(arr1[i] < arr2[j]) {
            i++;
        } else {
            j++;
        }
    }
}


// Brute Force approach
// Time Complexity: O(N*M)
// Space Complexity: O(1)
void intersectionOfTwoNonSortedArr(int *arr1, int n, int *arr2, int m, int *intersection) {
    int k = 0;
    if(n == 0 || m == 0) {
        cout << "One array is empty!" << endl;
        return;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(arr1[i] == arr2[j]) {
                intersection[k++] = arr1[i];
                arr2[j] = INT_MIN;
                break;
            }
        }
    }

    // If order is matter then use sort (TC: k log k) but it will increase time complexity of program.
    sort(intersection, intersection + k); // Time Complexity: O(n * m + k log k)
}

int main() {
    int arr1[10] = {9, 4, 4, 5};
    int arr2[10] = {9, 4, 9, 8, 4};
    int n = 4, m = 5;
    int intersection[10], i = 0;

    for(int i = 0; i < 10; i++)
        intersection[i] = INT_MIN;

    intersectionOfTwoNonSortedArr_um(arr1, n, arr2, m, intersection);

    cout << "Intersection of two Non-Sorted arrays: ";
    while(i < 10) {
        if(intersection[i] == INT_MIN) {
            if(intersection[0] == INT_MIN) 
                cout << "No intersection :(" << endl;
            break;
        }
        cout << intersection[i] << " ";
        i++;
    }

    cout << endl;
    return 0;
}