#include <iostream>

void merge(int a[],int b[],int* out){
    int i = 0, j = 0, k = 0;
    int n = a.size(), m = b.size(); //IS THIS LEGAL?
    while(i < n && j < m){
        if(a[i]<=b[j]){
            out[k] = a[i];
            i++;
            k++;
        }else{
            out[k] = b[j];
            j++;
            k++;
        }
    }
    while(i < n){
        out[k] = a[i];
        i++;
        k++;
    }
    while(j < m){
        out[k] = b[j];
        j++;
        k++;
    }
}

int* mergeSort(int a[], int n){
    if(n==1) return a;
    //Split arr in half
    return merge(mergeSort(first,SIZE OF FIRST),mergeSort(last, SIZE OF LAST));
}

int main()
{
    using namespace std;
    
    int arr[7];
    int sorted[7];
    }
    
}
