#include <iostream>
#include <string>
#include <map>

int merge(int a[],int x,int b[],int y){
    int i = 0, j = 0, numSorted = 0;
    int out[x+y];
    while(i < x && j < y){
        if(i <= j){
            out[numSorted] = a[i];
            i++
        }
        else{
            out[numSorted] = b[j];
            j++
        }
    }
}

int mergeSort(const int& a[],int n){
    int first[n/2];
    int second[n - (n/2)];
    if(n==1) return a[];
    for(int i = 0; i < n/2; i++){
        first[i]=a[i];
    }
    for(int i = n/2 + 1; i < n; i++){
        last[i]=a[i];
    }
    return merge(mergeSort(first,n/2),n/2,mergeSort(last,n/2-1),n/2-1);
}

int main()
{
    using namespace std;
    
    int unsorted[7];
    int sorted[7];
    unsorted = {1,2,3,2,6,3,1};
    sorted = mergeSort(unsorted,7);
    
}
