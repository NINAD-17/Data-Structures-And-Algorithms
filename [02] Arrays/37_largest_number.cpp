#include <bits/stdc++.h>
using namespace std;

string largestNumber(vector<int> &nums) {
    // Step 1: Convert all integers to string
    vector<string> strNums;

    for(auto num : nums)
        strNums.push_back(to_string(num));

    // Step 2: Sort using custom comparator (A + B > B + A)
    sort(strNums.begin(), strNums.end(),
         [](const string &a, const string &b) { return a + b > b + a; });

    // Step 3: Handle edge case where all numbers are 0
    if(strNums[0] == "0")
        return "0";

    // Step 4: Concatenate sorted strings
    string result = "";
    for(const string &s : strNums)
        result += s;

    return result;
}

int main() { return 0; }