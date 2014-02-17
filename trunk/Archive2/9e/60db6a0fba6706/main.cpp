#include <iostream>

void merge(int* a,int x,int* b,int y){
    int i = 0, j = 0, numSorted = 0;
    int length = x + y;
    int out[length];
    while(i < x && j < y){
        if(i <= j){
            out[numSorted] = a[i];
            i++;
        }
        else{
            out[numSorted] = b[j];
            j++;
        }
    }
    a = out;
}

void mergeSort(int* a,int n){
    int* firstHalf          = a;
    int  firstHalfLength    = n/2;
    int* secondHalf         = a + n/2 + 1;
    int secondHalfLength   = n - n/2;
    if(n<=1) return;
    else merge(mergeSort(firstHalf,firstHalfLength),firstHalfLength,mergeSort(secondHalf,secondHalfLength),secondHalfLength);
}

int main()
{
    using namespace std;
    
    int arr[7];
    arr = {1,2,3,2,6,3,1};
    mergeSort(arr,7);
    for(int i = 0; i < 7; i++){
        cout << arr[i] << " ";
    }
    
}
