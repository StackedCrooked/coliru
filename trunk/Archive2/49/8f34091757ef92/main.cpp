#include <iostream>

struct Range{
    int* start;
    int* end;
    int length(){ return end - start; };
};

void merge(Range a, Range b,int* out){
    int i = 0, j = 0, k = 0;
    while(i < a.length() && j < b.length()){
        if(a.start[i]<=b.start[j]){
            out[k] = a.start[i];
            i++;
            k++;
        }else{
            out[k] = b.start[j];
            j++;
            k++;
        }
    }
    while(i < a.length()){
        out[k] = a.start[i];
        i++;
        k++;
    }
    while(j < b.length()){
        out[k] = b.start[j];
        j++;
        k++;
    }
}

void mergeSort(int* a, int n){
    if(n==1){ return; }
    
    //Split arr in half
    Range first;
    first.start = a;
    first.end = a + n/2;
    Range last;
    last.start = a + n/2;
    last.end = a + n;
    
    //Do they need further cutting and merging?
    mergeSort(first.start,first.length());
    mergeSort(last.start,last.length());
    
    //Merge the two halves
    int* mergedArray = new int;
    merge(first,last,mergedArray);
    a = mergedArray;
}

int main()
{
    using namespace std;
    
    int arr[] = { 1, 2, 3, 2, 6, 3, 1} ;
    mergeSort(arr,7);
    for(int i = 0; i < 7; i++){
        cout << arr[i] << " ";
    }
    
}
