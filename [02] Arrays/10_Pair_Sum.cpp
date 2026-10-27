#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

// Extended Optimal Approach - In this all pairs are sorted by first element as well as second.
// First compare the first element of each pair.
// If they’re equal, compare the second element.
// Example:
//     - (1,4) comes before (2,3) because 1 < 2.
//     - (2,3) comes before (2,5) because 3 < 5.

// Time complexity: O(n log n)
// Space: O(log n) because of sort()
void pairSum2_extended(int *arr, int n, int sum, int *pairsArr) {
    vector<pair<int, int>> result; // vector of pairs
    sort(arr, arr + n);

    int st = 0, en = n - 1;
    while(st <= en) {
        if(arr[st] + arr[en] == sum) {
            result.push_back({arr[st], arr[en]});
            st++, en--;
        } else if(arr[st] + arr[en] > sum) {
            en--;
        } else {
            st++;
        }
    }

    sort(result.begin(), result.end()); // sorts lexicographically: compares pair.first; breaks ties using pair.second.
}

// Optimal approach
// Time Complexity: O(n log n)
// Space Complexity: O(log n) -> sort() takes O(log n) space for recursion
void pairSum2(int *arr, int n, int sum, int *pairsArr) {
    int k = 0; 
    sort(arr, arr + n); // Sort array

    int st = 0, en = n - 1; // Two pointers
    while(st <= en) {
        if(arr[st] + arr[en] == sum) {
            pairsArr[k] = arr[st];
            pairsArr[k + 1] = arr[en];
            st++, en--, k += 2;
        }
        else if(arr[st] + arr[en] > sum) 
            en--;
        else 
            st++;
    }
}

// Brute Force Approach
// Time Complexity: O(n^2)
// Space Complexity: O(log n) for sort()
void pairSum(int *arr, int n, int sum, int *pairsArr) {
    int k = 0;

    // If you want to sort this array by 1st element in that pair
    sort(arr, arr + n); // If you use sort then time complexity: O(n^2 + n log(n))

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] + arr[j] == sum) {
                if(arr[i] <= arr[j]) {
                    pairsArr[k] = arr[i];
                    pairsArr[k + 1] = arr[j];
                } else {
                    pairsArr[k] = arr[j];
                    pairsArr[k + 1] = arr[i];
                }
                k += 2;
            }
        }
    }
}

int main() {
    int arr[10] = {5, 3, 2, 4, 1}, pairsArr[10];
    int n = 5, reqSum = 5;

    for(int i = 0; i < 10; i++) 
        pairsArr[i] = INT_MIN;
    
    pairSum2(arr, n, reqSum, pairsArr);
    if(pairsArr[0] == INT_MIN)
        cout << "No pair found :(" << endl;
    else {
        for(int i = 0; i < 10; i+=2) {
            if(pairsArr[i] == INT_MIN)
                return 0;
            cout << "Pair-" << i + 1 << " -> " << pairsArr[i] << ", " << pairsArr[i + 1] << endl;
        }
    }

    cout << endl;
    return 0;
}