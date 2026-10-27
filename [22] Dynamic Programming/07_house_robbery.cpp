#include <bits/stdc++.h>
using namespace std;

int usingOptimizedTabulation_forHouseRobbery(vector<int> &nums, int start, int end) {
    int prev2 = 0;
    int prev1 = nums[start];

    for(int i = start + 1; i <= end; i++) {
        int incl = prev2 + nums[i];
        int excl = prev1;
        int ans = max(incl, excl);
        prev2 = prev1;
        prev1 = ans;
    }

    return prev1;
}

// Time: O(n)
// Space: O(1) because we used indices instead of copying vector values in new vector
int houseRobberSpaceOptimized(vector<int> &valueInHouse) {
    int n = valueInHouse.size();

    if(n == 1)
        return valueInHouse[0];

    // Case 1: Rob houses from 0 to n-2
    int case1 = usingOptimizedTabulation_forHouseRobbery(valueInHouse, 0, n - 2);

    // Case 2: Rob houses from 1 to n-1
    int case2 = usingOptimizedTabulation_forHouseRobbery(valueInHouse, 1, n - 1);

    return max(case1, case2);
}

// Time: O(n)
// Space: O(1)
int usingOptimizedTabulation(vector<int> &nums) {
    int n = nums.size();

    // vector<int> dp(n, 0);
    int prev2 = 0;
    int prev1 = nums[0];

    for(int i = 1; i < n; i++) {
        int incl = prev2 + nums[i];
        int excl = prev1 + 0;
        int ans = max(incl, excl);
        prev2 = prev1;
        prev1 = ans;
    }
    
    return prev1;
}

// Time: O(n)
// Space: O(n)
int houseRobber(vector<int> &valueInHouse) {
    int n = valueInHouse.size();

    if(n == 1)
        return valueInHouse[0];

    vector<int> first, second;
    for(int i = 0; i < n; i++) {
        if(i != n - 1)
            first.push_back(valueInHouse[i]); // 0 to n - 2
        
        if(i != 0)
            second.push_back(valueInHouse[i]); // 1 to n - 1
    }

    return max(usingOptimizedTabulation(first), usingOptimizedTabulation(second));
}

int main() {
    vector<int> valueInHouse = {1, 3, 2, 4};

    cout << houseRobber(valueInHouse) << endl;
    cout << houseRobberSpaceOptimized(valueInHouse) << endl;

    return 0;
}