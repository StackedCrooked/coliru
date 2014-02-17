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

Range mergeSort(int a[], int n){
    Range ret;
    ret.start = a;
    ret.end = a + n;
    if(n==1){ return ret; }
    
    //Split arr in half
    Range first;
    first.start = a;
    first.end = a + n/2;
    Range last;
    last.start = a + n/2;
    last.end = a + n;
    
    //Merge the two halves
    merge(mergeSort(first.start,first.length()),mergeSort(last.start,last.length()),a);
    
    //Return the range of the merged halves
    return ret;
}

int main()
{
    using namespace std;
    
    int arr[7];
    int sorted[7];
    sorted = mergeSort(arr,7).start;
    for(int i = 0; i < 7; i++){
        cout << sorted[i] << " ";
    }
    
}
