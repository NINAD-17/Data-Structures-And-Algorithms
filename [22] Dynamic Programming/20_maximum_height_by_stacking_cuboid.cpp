#include <bits/stdc++.h>
using namespace std;

bool check(vector<int> base, vector<int> newBox) {
    if(newBox[0] <= base[0] && newBox[1] <= base[1] && newBox[2] <= base[2])
        return true;
    else
        return false;
}

int LIS(vector<vector<int>> &cuboids, int n) {
    vector<int> curr(n + 1, 0); // current row
    vector<int> next(n + 1, 0); // next row

    for(int currIndex = n - 1; currIndex >= 0; currIndex--) {
        for(int prevIndex = currIndex - 1; prevIndex >= -1; prevIndex--) {
            int include = 0;
            if(prevIndex == -1 || check(cuboids[currIndex], cuboids[prevIndex]))
                include = cuboids[currIndex][2] + next[currIndex + 1];

            // Exclude
            int exclude = 0 + next[prevIndex + 1];

            curr[prevIndex + 1] = max(include, exclude);
        }
        
        next = curr;
    }

    return next[0];
}

int maxHeight(vector<vector<int>> &cuboids) {
    // Step 1: Sort all dimensions for every cuboid
    for(auto &cuboid: cuboids) {
        sort(cuboid.begin(), cuboid.end());
    }

    // Step 2: Sort all cuboids basis on width and length
    sort(cuboids.begin(), cuboids.end());

    // Step 3: Use logic of LIS
    return LIS(cuboids, cuboids.size());
}

int main() {

}