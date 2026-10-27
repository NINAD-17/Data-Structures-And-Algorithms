#include <bits/stdc++.h>
using namespace std;

// Optimized Approach with one pass
// Time Complexity: O(n)
// Space Complexity: O(1)
int longestMountain(vector<int> &arr) {
    int n = arr.size();
    int maxLen = 0;
    int up = 0;
    int down = 0;

    for(int i = 1; i < n; i++) {
        // Case 1: Plateau or starting a new climb after a descent
        if((down > 0 && arr[i] > arr[i - 1]) || arr[i] == arr[i - 1]) {
            up = 0;
            down = 0;
        }

        // Case 2: Climbing up
        if(arr[i] > arr[i - 1]) {
            up++;
        }

        // Case 3: Going down (only valid if we already climbed)
        if(arr[i] < arr[i - 1]) {
            if(up > 0) {
                down++;
                maxLen = max(maxLen, up + down + 1);
            }
        }
    }

    return maxLen;
}

// It is an optimal two-pointer expansion algorithm, very similar to the
// standard $O(n)$ "Expand Around Center" technique used in Longest Palindromic
// Substring. 
// Time Complexity: O(n)
//      An algorithm is $O(n^2)$ only if operations repeat proportional to $n$
//      times across $n$ steps ($n \times n$). Visiting elements twice or three
//      times does not make an algorithm $O(n^2)$—it makes it $2n$ or $3n$,
//      which is still strictly $O(n)$.
// Space Complexity: O(1)
int longestMountain_2(vector<int> &arr) {
    int n = arr.size();
    if(n < 3)
        return 0;

    int maxLen = 0;

    // A peak cannot be at index 0 or index n - 1
    for(int i = 1; i < n - 1; i++) {
        // Step 1: Check if arr[i] is a peak
        if(arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {

            // Step 2: Expand left down the mountain
            int left = i;
            while(left > 0 && arr[left] > arr[left - 1]) {
                left--;
            }

            // Step 3: Expand right down the mountain
            int right = i;
            while(right < n - 1 && arr[right] > arr[right + 1]) {
                right++;
            }

            // Step 4: Calculate length and update max
            int currentLen = right - left + 1;
            maxLen = max(maxLen, currentLen);

            // Optimization: Skip to 'right' because no new peak
            // can exist inside the descending slope!
            i = right;
        }
    }

    return maxLen;
}