#include <iostream>
using namespace std;

// Tower of Hanoi
// Time Complexity: O(2^n) as total moves are (2^n - 1)

// Goal: Move 'n' disks from Source (A) to Destination (C) using Helper (B)
// Step 1: Move top (n - 1) disks from A -> B   (using C as helper)
// Step 2: Move the remaining 1 disk from A -> C (direct move)
// Step 3: Move the (n - 1) disks from B -> C   (using A as helper)

void towerOfHanoi(int disks, char from_rod, char to_rod, char aux_rod) {
    // Base Case: Only 1 disk left to move
    if(disks == 1) {
        cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
        return ;
    }

    // Step 1: Move top (n - 1) disks from from_rod -> aux_rod (using to_rod as helper)
    towerOfHanoi(disks - 1, from_rod, aux_rod, to_rod);

    // Step 2: Move the nth largest disk directly from from_rod -> to_rod
    cout << "Move disk " << disks << " from " << from_rod << " to " << to_rod << endl;

    // Step 3: Move the (n - 1) disks from aux_rod -> to_rod (using from_rod as helper)
    towerOfHanoi(disks - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int disks = 3;

    towerOfHanoi(disks, 'A', 'B', 'C'); // Move 3 disks from A to C using B
    return 0;
}