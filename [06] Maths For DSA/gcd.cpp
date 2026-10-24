#include <iostream>
using namespace std;

// Stein Algorithm (Binary GCD)
// Time Complexity: O(log(min(a, b)))
// Space complexity: O(1)
int findGCD_UsingBinaryGCDAlgo(int num1, int num2) {
    if(num1 == 0)
        return num2;
    
    if(num2 == 0)
        return num1;
    
    int shift;
    for(shift = 0; ((num1 | num2) & 1) == 0; shift++) {
        num1 >>= 1;
        num2 >>= 1;
    }

    while((num1 & 1) == 0) 
        num1 >>= 1;
    
    do {
        while((num2 & 1) == 0)
            num2 >>= 1;
        
        if(num1 > num2)
            swap(num1, num2);

        num2 = num2 - num1;
    } while(num2 != 0);

    return num1 << shift;
}

// Same solution as above but by using normal operators instead of bitwise
// Remember: Bitwise operators are more efficient than normal -- Learn more in readme.md
int findGCD_UsingBinaryGCDAlgo_2(int num1, int num2) {
    if(num1 == 0)
        return num2;
    
    if(num2 == 0)
        return num1;
    
    int shift;
    for(shift = 0; (num1 % 2 == 0) && (num2 % 2 == 0); shift++) {
        num1 /= 2;
        num2 /= 2;
    }

    while(num1 % 2 == 0) 
        num1 /= 2;
    
    do {
        while(num2 % 2 == 0)
            num2 /= 2;
        
        if(num1 > num2)
            swap(num1, num2);

        num2 = num2 - num1;
    } while(num2 != 0);

    return num1 << shift;
} 


// -- Euclidean Algorithm
// Time Complexity: O(log(min(num1, num2)))
//      In Euclid's algorithm, after every iteration we replace the smaller number by the remainder. Since the remainder is always smaller than the current smaller number, the algorithm's progress depends on how quickly the smaller number shrinks. 
//      Therefore the running time is proportional to the logarithm of the smaller input, giving O(log(min(a,b))).
//      In every iteration, new b = old a % old b and remainder is always smaller than old b. Therefore b keeps shrinking until it becomes 0.
//      That's the real reason why Euclid's Algorithm takes O(log(min(a,b))).
// Space Complexity : O(1) 
int findGCD_UsingModulus(int num1, int num2) {
    while(num2 != 0) {
        int temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }

    return num1;
}


// -- Euclidean Substraction Method OR Naive Euclidean
// Time Complexity: O(max(num1, num2))
// Space Complexity: O(1)
int findGCD_UsingSubstraction(int num1, int num2) {
    if(num1 == 0) 
        return num2;

    if(num2 == 0)
        return num1;
    
    while(num1 != num2) {
        if(num1 > num2) 
            num1 = num1 - num2;
        else
            num2 = num2 - num1;
    }

    return num1;
}


// -- Brute Force
// Time Complexity: O(min(num1, num2))
// Space Complexity: O(1)
int findGCD_BruteForce(int num1, int num2) {
    int ans = 1;

    for(int i = 0; i <= min(num1, num2); i++) {
        if((num1 % i) == 0 && (num2 % i) == 0)
            ans = i;
    }

    return ans;
}

int main() {
    int num1, num2;

    cout << "Enter number-1: "; cin >> num1;
    cout << "Enter number-2: "; cin >> num2;

    cout << "GCD of numbers " << num1 << " and " << num2 << " is " << findGCD_UsingBinaryGCDAlgo(num1, num2) << endl;
    return 0;
}