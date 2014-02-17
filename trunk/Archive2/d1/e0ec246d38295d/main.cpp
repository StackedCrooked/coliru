#include <iostream>

struct HORange{
    int* start;
    int* end;
};

void merge(HORange a, HORange b, int n,int* out){
    int i = 0, j = 0, numSorted = 0;
    while(out + i <= a.end && out + j <= b.end){
        if(a.start[i] <= b.start[j]){
            out[numSorted] = a.start[i];
            i++;
        }
        else{
            out[numSorted] = b.start[j];
            j++;
        }
    }
}

void mergeSort(int* a,int n,int* toBeSorted){
    HORange first;
    HORange last;
    first.start = a;
    first.end = a + n/2;
    last.start = a + (n - n/2);
    last.end = a + n;
    if(n<=1) return;
    else merge(first,last,n,toBeSorted);
}

int main()
{
    using namespace std;
    
    int arr[7];
    int sorted[7];
    arr = {1,2,3,2,6,3,1};
    mergeSort(arr,7,sorted);
    for(int i = 0; i < 7; i++){
        cout << arr[i] << " ";
    }
    
}
