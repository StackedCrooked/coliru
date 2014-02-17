#include <iostream>

// Copies the contents of half-open range [begin, end) into a range starting at `dest`
void copy(int* begin, int* last, int* dest) {
    while ( begin != last ) *dest++ = *begin++;
}

struct Range
{
    int* first;
    int* last;
    Range( int* firstptr, int* lastptr ) {
        first = firstptr;
        last = lastptr;
    }
    
    // Returns `true` if the range is empty
    bool empty() const { return first == last; }
    // Returns the size of the range
    int size() const { return last - first; }
};

void merge(Range a, Range b, Range out) {
    while ( 1 ) {
        
    }
}

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
    //TODO: Split arr in half
    return merge(mergeSort(first,SIZE OF FIRST),mergeSort(last, SIZE OF LAST),a);
}

int main()
{
    using namespace std;
    
    int arr[7];
    int sorted[7];
    }
    
}
