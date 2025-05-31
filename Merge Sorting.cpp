//Merge Sort
#include <iostream>
#include <vector>
using namespace std;

//Merge two sub-arrays
void merge(vector<int> &arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Create temp Arrays
    vector<int> l(n1), r(n2);

    //Copy data
    for(int i = 0; i < n1; i++){
        l[i]  = arr[left + i];
    }
    for(int i = 0; i < n2; i++){
        r[i]  = arr[mid + 1 + i];
    }

    // Merge temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2){
        if(l[i] <= r[j]){
            arr[k++] = l[i++];
        }
        else{
            arr[k++] = r[j++];
        }
    }

    //Copy remaining Elements
    while(i < n1){
        arr[k++] = l[i++];
    }
    while(j < n2){
        arr[k++]= r[j++];
    }

}

//Merge-Sort Function
void mergeSort(vector<int>& arr, int left, int right){
    if(left < right){
        int mid = (left + right)/2;

        //Sort first and second halves;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> arr = {54, -12, 12, 3, 547};
 
    int n = arr.size();

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array (Merge Sort): ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}