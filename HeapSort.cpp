#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
using namespace std;

void maxHeapify(vector<int>&arr, int n, int i){
    int largest = i;
    int l = (i*2) + 1;
    int r = (i * 2 ) + 2;
    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }
    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }
    if(largest != i){
        swap(arr[largest], arr[i]);
        maxHeapify(arr, n, largest);
    }
}


void heapSort(vector<int>&arr, int n){
    for(int i = n /2 - 1; i >= 0; i--){ //building the maxHeap
        maxHeapify(arr, n, i);
    }
    for(int i = n - 1; i > 0; i--){ //deletion in decending order
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0); //reduces heap size is i
    }
}

int main(){
    vector <int> arr;
    string input;
    int num;

    getline(cin, input);
    istringstream stream(input);

    while(stream >> num){
        arr.push_back(num);
    }

    int size = arr.size();
    heapSort(arr, size);

    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}