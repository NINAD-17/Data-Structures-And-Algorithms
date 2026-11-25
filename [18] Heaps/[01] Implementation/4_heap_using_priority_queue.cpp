#include <iostream>
#include <queue> // You'll need to include this header file
using namespace std;

int main() {
    // max heap
    priority_queue<int> pq;

    pq.push(4);
    pq.push(2);
    pq.push(5);
    pq.push(3);

    cout << "top: " << pq.top() << endl;
    pq.pop();

    cout << "top: " << pq.top() << endl;
    cout << "size: " << pq.size() << endl;

    if(pq.empty()) 
        cout << "pq is empty" << endl;
    else 
        cout << "pq isn't empty" << endl;


    // min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(4);
    minHeap.push(2);
    minHeap.push(5);
    minHeap.push(3);

    cout << "top: " << minHeap.top() << endl;
    minHeap.pop();

    cout << "top: " << minHeap.top() << endl;
    cout << "size: " << minHeap.size() << endl;

    if(minHeap.empty()) 
        cout << "pq is empty" << endl;
    else 
        cout << "pq isn't empty" << endl;
}