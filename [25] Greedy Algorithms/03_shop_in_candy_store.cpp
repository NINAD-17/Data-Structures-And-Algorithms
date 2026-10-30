#include <bits/stdc++.h>
using namespace std;

// Shop in candy store
// Find: 
//      - Min amount of money by which we can buy all the candies.
//      - Max amount of money by which we can buy all the candies.

// Time: O(N log N)
// Space: O(1)
vector<int> candyStore(vector<int> &candies, int k) {
    sort(candies.begin(), candies.end());

    int minAmt = 0;
    int buy = 0;
    int free = candies.size() - 1;

    while(buy <= free) {
        minAmt += candies[buy];
        buy++;
        free -= k;
    }

    int maxAmt = 0;
    buy = candies.size() - 1;
    free = 0;

    while(free <= buy) {
        maxAmt += candies[buy];
        buy--;
        free += k;
    }

    return {minAmt, maxAmt};
}

int main() {
    vector<int> candies = {3, 2, 1, 4};
    int k = 2;

    vector<int> ans = candyStore(candies, k);
    
    cout << "Minimum amount: " << ans[0] << endl;
    cout << "Maximum amount: " << ans[1] << endl;

    return 0;
}