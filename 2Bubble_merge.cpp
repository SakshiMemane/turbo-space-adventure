#include <iostream>
#include <omp.h>
using namespace std;

void parallel_bubble_sort(int arr[], int n){
    #pragma omp parallel
    {
        int i, temp, flag = 1;
        while(flag){
            flag = 0;
            #pragma omp parallel for
            for(i = 0; i < n-1; i++){
                if(arr[i] > arr[i+1]){
                    temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                    flag = 1;
                }
            }
        }
    }
}
void Merge(int a[], int low, int high, int mid)
{
    int i, j, k, temp[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;
    while (i <= mid && j <= high){
        if (a[i] < a[j]){
            temp[k] = a[i];
            k++;
            i++;
        }
        else{
            temp[k] = a[j];
            k++;
            j++;
        }
    }
    while (i <= mid){
        temp[k] = a[i];
        k++;
        i++;
    }
    while (j <= high){
        temp[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i <= high; i++){
        a[i] = temp[i-low];
    }
}

void MergeSort(int *a, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                MergeSort(a, low, mid);
            }
            #pragma omp section
            {
                MergeSort(a, mid+1, high);
            }
        }
        Merge(a, low, high, mid);
    }
}

int main() {
    int arr[] = {6,4,2,8,7,9,5,1,3};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Input Array: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    
    cout << endl;
    
    parallel_bubble_sort(arr,n);
    cout << "Sorted Array using parallel bubble sort: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    
    cout << endl;
    
    MergeSort(arr, 0, n-1);
    cout << "Sorted Array using parallel merge sort: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}

