#include <bits/stdc++.h>
using namespace std;

void merge(vector<pair<int, int>> &items, vector<pair<int, int>> &temp, vector<int> &count, int left, int mid, int right) {
    int i = left;       // Pointer for left
    int j = mid + 1;    // Pointer for right
    int k = left;       // Pointer for temp array
    int rightCount = 0; // Number of elements from right half smaller than current left element

    while(i <= mid && j <= right) {
        if(items[j].first < items[i].first) {
            rightCount++;
            temp[k++] = items[j++];
        } else {
            count[items[i].second] += rightCount;
            temp[k++] = items[i++];
        }
    }

    // Flush remaining left elements
    while(i <= mid) {
        count[items[i].second] += rightCount;
        temp[k++] = items[i++];
    }

    // Flush remaining right elements
    while(j <= right) {
        temp[k++] = items[j++];
    }

    // Copy back to original items array
    for(int idx = left; idx <= right; idx++) {
        items[idx] = temp[idx];
    }
}

void mergeSort(vector<pair<int, int>> &items, vector<pair<int, int>> &temp, vector<int> &count, int left, int right) {
    if(left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(items, temp, count, left, mid);
    mergeSort(items, temp, count, mid + 1, right);

    merge(items, temp, count, left, mid, right);
}

vector<int> countSmaller(vector<int> &nums) {
    int n = nums.size();
    vector<int> count(n, 0);

    // Store pair of {value, original_index}
    vector<pair<int, int>> items(n);

    for(int i = 0; i < n; i++)
        items[i] = make_pair(nums[i], i); // OR {nums[i], i}

    vector<pair<int, int>> temp(n);
    mergeSort(items, temp, count, 0, n - 1);

    return count;
}

int main() {
    vector<int> nums = {5, 2, 6, 1};

    vector<int> count = countSmaller(nums);

    for(int i = 0; i < count.size(); i++)
        cout << count[i] << " ";
    cout << endl;

    return 0;
}