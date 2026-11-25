#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

// Using Priority Queue
// Time: O(n)
//       Heap operations (push/pop) run on at most 3 elements ($O(\log 3) = O(1)$), and unordered_set lookups are $O(1)$ on average.
// Space: O(n)
//       $O(n)$ — Due to the unordered_set storing unique elements (the minHeap itself takes $O(1)$ space because at max only 3 elements it stores).
int thirdMaxUsingPQ(int *arr, int n) {
    // Min Heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    unordered_set<int> seen;

    for(int i = 0; i < n; i++) {
        if(seen.count(arr[i])) {
            continue;
        }

        seen.insert(arr[i]);

        if(minHeap.size() < 3) {
            minHeap.push(arr[i]);
        } else if(minHeap.top() < arr[i]) {
            minHeap.pop();
            minHeap.push(arr[i]);
        }
    }

    // If we found 3 distinct maximums, the top of the min-heap is the 3rd max
    if(minHeap.size() == 3) {
        return minHeap.top();
    }

    // Otherwise (fewer than 3 distinct elements), return the largest element
    int maxVal = minHeap.top();
    while(!minHeap.empty()) {
        maxVal = max(maxVal, minHeap.top());
        minHeap.pop();
    }

    return maxVal;
}

// Best Solution: In place algorithm
// Time Complexity: O(n)
// Space Complexity: O(1)
int thirdMax(int *arr, int n) {
    if(n == 1) 
        return arr[0]; // If size is 1 then return max num as arr[0]
    
    if(n == 2)
        return max(arr[0], arr[1]); // If size is 2 then return max num from value of 0th index and 1th index.

    int firstMax = *max_element(arr, arr + n); // finding max element from whole array
    int secondMax = INT_MIN;
    int thirdMax = INT_MIN;
    int count = 0; // count -> to check if we found second max element or not if not then we will return firstMax. When it will happen? when all values are similar such as 3, 3, 3, 3
    for(int i = 0; i < n; i++) {
        if(secondMax < arr[i] && arr[i] != firstMax) {
            secondMax = arr[i];
            count++;
        }
    }

    if(count == 0)
        return firstMax; // As we've not found any second max we're returning firstMax
    
    count = 0; // Reset count to 0. to find thirdMax is exist or not
    for(int i = 0; i < n; i++) {
        if ((thirdMax < arr[i] || arr[i] == INT_MIN) && (arr[i] != firstMax && arr[i] != secondMax)) {
            thirdMax = arr[i];
            count++;
        }
    }

    if(count > 0)
        return thirdMax;
    else
        return firstMax; // When there is no third max -> condition {1, 2, 2, 2}
}

// Using Set
// Time/space complexity: O(n)
int thirdMaxUsingSet(int *arr, int n) {
    set<int> s; // To only store unique numbers in sorted order.
    for(int i = 0; i < n; i++)
        s.insert(arr[i]);
    
    if(s.size() >= 3) {
        int thirdIndexFromLast = s.size() - 3;
        auto thirdMax = next(s.begin(), thirdIndexFromLast); // next function to advance the begin iterator of the set s by Third_index_from_last positions. The begin iterator points to the first element in the set, and advancing it by Third_index_from_last positions means it now points to the third element from the end of the set. This is because the elements in a set are stored in ascending order, so the third element from the end is also the third maximum value in the set.
        return *thirdMax;
    }

    return *(--s.end()); // If the vector does not contain at least three distinct values, the function returns the maximum value in the vector. therefore we're 1st decrementing s.end() to reach last position.
    // The * operator is used to dereference a pointer or iterator, which means it returns the value stored at the memory location pointed to by the pointer or iterator.
}

// Time Complexity: O(n log(n))
void thirdDistinctMax(int *arr, int n) {
    sort(arr, arr + n, greater<int>());

    int fDistinctMax = arr[0];
    int sDistinctMax = arr[1];
    int tDistinctMax = arr[2];

    if(arr[1] == arr[0]) {
        for(int i = 2; i < n; i++) {
            if(arr[i] != arr[0]) {
                sDistinctMax = arr[i];
                break;
            }
        }
    }

    if(arr[2] == arr[1] || arr[2] == arr[0]) {
        for(int i = 2; i < n; i++) {
            if(arr[i] != arr[0] && arr[i] != arr[1]) {
                tDistinctMax = arr[i];
                break;
            }
        }
    }

    cout << "The first distinct maximum is " << fDistinctMax << "." << endl;
    cout << "The second distinct maximum is " << sDistinctMax << "." << endl;
    cout << "The third distinct maximum is " << tDistinctMax << "." << endl;
}

int main() {
    int arr[10] = {2,2,3,1};
    int n = 4;

    thirdDistinctMax(arr, n);
    cout << "Third Max using set: " << thirdMaxUsingSet(arr, n) << endl; 
    cout << "Third Max using inplace algorithm is " << thirdMax(arr, n) << endl;

    return 0;
}