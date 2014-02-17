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

void mergeSort(int* a, int n, int* dest){
    if(n==1){ return; }
    
    //Split arr in half
    Range first;
    first.start = a;
    first.end = a + n/2;
    Range last;
    last.start = a + n/2;
    last.end = a + n;
    
    //Do they need further cutting and merging?
    mergeSort(first.start,first.length(), dest);
    mergeSort(last.start,last.length(), dest + n/2);
    
    //Merge the two halves
    merge(first,last,dest);
}

int main()
{
    using namespace std;
    
    int arr[] = { 1, 2, 3, 2, 6, 3, 1};
    int dest[7];
    mergeSort(arr,7,dest);
    for(int i = 0; i < 7; i++){
        cout << dest[i] << " ";
    }
    
}
