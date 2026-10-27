#include <bits/stdc++.h>
using namespace std;

// Optimal Solution with one pass only
// Dutch National Flag Algorithm:
//      This famous algorithm was designed by Edsger Dijkstra.
//      It partitions the array into three sections using three pointers:
//          1. low: Boundary for 0s (everything before low is strictly 0).
//          2. mid: Current element being inspected (everything between low and
//          mid - 1 is strictly 1).
//          3. high: Boundary for 2s (everything after high is strictly 2).
//      [ 0 0 0 ... | 1 1 1 ... |  Unprocessed elements  | 2 2 2 ... ] - here
//      `|` are low, mid and high respectively.
// Leetcode: https://leetcode.com/problems/sort-colors/
void sortColors(vector<int> &nums) {
    // Dutch National Flag Algorithm
    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;

    while(mid <= high) {
        if(nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if(nums[mid] == 1) {
            mid++;
        } else {
            // Case: nums[mid] == 2
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

// Brute Force (uses two pass - one to count and other to write)
// Time Complexity: O(n)
// Space Complexity: O(1)
void sort_0_1_2(int *arr, int n) {
    int count_0 = 0, count_1 = 0, count_2 = 0;

    for(int i = 0; i < n; i++) {
        if(arr[i] == 0)
            count_0++;
        else if(arr[i] == 1)
            count_1++;
        else
            count_2++;

        arr[i] = 2;
    }

    cout << "Counts: " << count_0 << " " << count_1 << " " << count_2 << endl;

    int i = 0;

    while(count_0 > 0) {
        arr[i++] = 0;
        count_0--;
    }

    while(count_1 > 0) {
        arr[i++] = 1;
        count_1--;
    }

    while(count_2 > 0) {
        arr[i++] = 2;
        count_2--;
    }
}

int main() {
    int arr[10] = {0, 1, 2, 1, 2, 1, 2};
    int n = 7;

    sort_0_1_2(arr, n);

    // Output
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}