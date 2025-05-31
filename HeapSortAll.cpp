#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void minHeapify(vector<int>& heap, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < n && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

void deleteFromHeap(vector<int>& heap, int value) {
    int n = heap.size();
    int index = -1;

    //Finding the element to delete
    for (int i = 0; i < n; i++) {
        if (heap[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found in heap!" << endl;
        return;
    }

    //Replacing with the last element and remove last element
    heap[index] = heap[n - 1];
    heap.pop_back();
    n--;

    //Restoring heap property
    if (index > 0 && heap[index] < heap[(index - 1) / 2]) {
        // Heapify-Up if needed
        while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    } else {
        // Heapify-Down if needed
        minHeapify(heap, n, index);
    }
}

// Inserting an element into the Min-Heap
void insertToHeap(vector<int>& heap, int value) {
    heap.push_back(value);
    int i = heap.size() - 1;

    // Heapify-Up (Bubble-Up) to maintain Min-Heap property
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2; // Moving to parent index
    }
}

int getMin(const vector<int>& heap) {
    if (heap.empty()) {
        cout << "Heap is empty!" << "\n";
        return -1;
    }
    return heap[0]; // Root contains the minimum value
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int num ;
    vector<int> heap;
    cin >> num;
    for(int i = 0; i < num; i++){
        int type, value;
        cin >> type; // Read query type

        if (type == 1) { 
            cin >> value;
            insertToHeap(heap, value);
        } 
        else if (type == 2) { 
            cin >> value;
            deleteFromHeap(heap, value);
        } 
        else if (type == 3) {
            cout << getMin(heap) << "\n";
            
        }
    }
    return 0;
}

