#include <bits/stdc++.h>
using namespace std;

// Fractional Knapsack
// Given weights and values of N items, we need to put these items in a knapsack of
// capacity W to get the maximum total value in the knapsack.
// Note: Unlike 0/1 knapsack, you are allowed to break the item.

// Eg: N = 3, W = 50
// val -> [60 100 120]
// wt  -> [10 20 30]

// per unit value means val/wt. Ex - 60/10 = 6

// items[i].first = value, items[i].second = weight
double fractionalKnapsack(int capacity, vector<pair<int, int>> &items, int n) {
    // Sort items by value/weight in descending order
    // a.val / a.wt > b.val / b.wt  <=>  a.val * b.wt > b.val * a.wt (avoids floating point division)
    sort(items.begin(), items.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        double r1 = (double)a.first / a.second;
        double r2 = (double)b.first / b.second;
        return r1 > r2;
    });

    double totalVal = 0.0;
    int remainingCapacity = capacity;

    for(int i = 0; i < n; i++) {
        int val = items[i].first;
        int wt = items[i].second;

        if(wt <= remainingCapacity) {
            // Take the whole item
            totalVal += val;
            remainingCapacity -= wt;
        } else {
            // Take the fraction that fills the rest of the knapsack
            double perUnitVal = (double)val / wt;
            totalVal += remainingCapacity * perUnitVal;
            break; // Knapsack is completely full!
        }
    }

    return totalVal;
}

int main() {
    // {value, weight}
    vector<pair<int, int>> items = {{60, 10}, {100, 20}, {120, 30}};
    int capacity = 50;
    int n = items.size();

    cout << "Maximum value: " << fractionalKnapsack(capacity, items, n) << endl;

    return 0;
}