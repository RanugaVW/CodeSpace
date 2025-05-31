#include <iostream>
#include <sstream>
#include <algorithm> // for sort
#include <vector>
using namespace std;

void binarySearch(vector<int> arr, int target, int start, int end){
    if(start  > end){
        cout << "false";
        return;
    }

    int pivot = (start + end)/2;
    
    if (arr[pivot] == target){
        cout << "true";
        return;
    } 
    else{
        if(target > arr[pivot]){
            binarySearch(arr, target, pivot + 1, end);
        }
        else{
            binarySearch(arr, target, start, pivot - 1);
        }

    }
    
}


int main(){
    string input;
    int num;
    int target;
    vector<int> numbers;

    getline(cin, input);
    cin >> target;
    istringstream stream(input);

    while(stream >> num){
        numbers.push_back(num);
    }
    int size = numbers.size();
    sort(numbers.begin(), numbers.end());
    binarySearch(numbers, target, 0, size - 1);

    return 0;

}