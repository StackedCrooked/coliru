#include <ctime>
#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

void swap(int& x, int& y){
   int temp = x;
   x = y;
   y = temp;
}  // end swap

void choosePivot(int theArray[], int first, int last){
    cout << "enter choosePivot(array, " << first << ", " << last << ")\n";
    for(int i=first; i<last; ++i) std::cout << theArray[i] << ' '; std::cout << '\n';
    int mid = (last - first) / 2;
    if( (theArray[first] <= theArray[mid] &&
         theArray[mid] <= theArray[last]) ||
        (theArray[last] <= theArray[mid] &&
         theArray[mid] <= theArray[first]) ){
        // value at mid index is middle of values at first and last indices 
        swap(theArray[first], theArray[mid]);
    }else if( (theArray[first] <= theArray[last] &&
               theArray[last] <= theArray[mid]) ||
              (theArray[mid] <= theArray[last] &&
               theArray[last] <= theArray[first])){
        // value at last index is middle of values
        swap(theArray[first], theArray[last]);
    }
    for(int i=first; i<last; ++i) std::cout << theArray[i] << ' '; std::cout << '\n';
    std::cout << "end choosePivot\n";
}

void partition(int theArray[],
               int first, int last, int& pivotIndex){
    std::cout << "enter partition(array, " << first << ", " << last << ")\n";
    for(int i=first; i<last; ++i) std::cout << theArray[i] << ' '; std::cout << '\n';
   // place pivot in theArray[first]
   choosePivot(theArray, first, last);
   int pivot = theArray[first];     // copy pivot

   // initially, everything but pivot is in unknown
   int lastS1 = first;           // index of last item in S1
   int firstUnknown = first + 1; // index of first item in
                                 // unknown

   // move one item at a time until unknown region is empty
   for (; firstUnknown <= last; ++firstUnknown)
   {  // Invariant: theArray[first+1..lastS1] < pivot
      //         theArray[lastS1+1..firstUnknown-1] >= pivot

      // move item from unknown to proper region
      if (theArray[firstUnknown] < pivot)
      {  // item from unknown belongs in S1
         ++lastS1;
         swap(theArray[firstUnknown], theArray[lastS1]);
         for(int i=first; i<last; ++i) std::cout << theArray[i] << ' '; std::cout << '\n';
      }  // end if

      // else item from unknown belongs in S2
   }  // end for

   // place pivot in proper position and mark its location
   swap(theArray[first], theArray[lastS1]);
   for(int i=first; i<last; ++i) std::cout << theArray[i] << ' '; std::cout << '\n';
   pivotIndex = lastS1;
    std::cout << "end partition\n";
}  // end partition

void quicksort(int theArray[], int first, int last){
    std::cout << "enter quicksort(array, " << first << ", " << last << ")\n";
    int pivotIndex;

   if (first < last)
   {  // create the partition: S1, pivot, S2
      for(int i=first; i<last; ++i) std::cout << theArray[i] << ' '; std::cout << '\n';
      partition(theArray, first, last, pivotIndex);

      // sort regions S1 and S2
      quicksort(theArray, first, pivotIndex-1);
      quicksort(theArray, pivotIndex+1, last);
   }  // end if
    std::cout << "end quicksort\n";
}  // end quicksort



void accuracy_test() {    
    {int array[3] = {0,0,0}; quicksort(array, 0, 3); assert(1 && std::is_sorted(array, array+3));}
    {int array[3] = {0,0,1}; quicksort(array, 0, 3); assert(2 && std::is_sorted(array, array+3));}
    {int array[3] = {0,1,0}; quicksort(array, 0, 3); assert(3 && std::is_sorted(array, array+3));}
    {int array[3] = {1,0,0}; quicksort(array, 0, 3); assert(4 && std::is_sorted(array, array+3));}
    {int array[3] = {0,1,1}; quicksort(array, 0, 3); assert(5 && std::is_sorted(array, array+3));}
    {int array[3] = {1,0,1}; quicksort(array, 0, 3); assert(6 && std::is_sorted(array, array+3));}
    {int array[3] = {1,1,0}; quicksort(array, 0, 3); assert(7 && std::is_sorted(array, array+3));}
    {int array[3] = {1,1,1}; quicksort(array, 0, 3); assert(8 && std::is_sorted(array, array+3));}
    {int array[3] = {0,1,2}; quicksort(array, 0, 3); assert(9 && std::is_sorted(array, array+3));}
    {int array[3] = {0,2,1}; quicksort(array, 0, 3); assert(10 && std::is_sorted(array, array+3));}
    {int array[3] = {1,0,2}; quicksort(array, 0, 3); assert(11 && std::is_sorted(array, array+3));}
    {int array[3] = {1,2,1}; quicksort(array, 0, 3); assert(12 && std::is_sorted(array, array+3));}
    {int array[3] = {2,0,1}; quicksort(array, 0, 3); assert(13 && std::is_sorted(array, array+3));}
    {int array[3] = {2,1,0}; quicksort(array, 0, 3); assert(14 && std::is_sorted(array, array+3));}
}

double diffclock(clock_t,clock_t) {return 0;}

int main(){
    accuracy_test();
    clock_t begin, end;//clocks to store number of ticks at beginning and end
    srand(time(NULL));//initialize seed
    cout << "# of Elements\tQuick\n";
    for(int n = 10; n < 100000; n*=10){
        int* array = new int[n];
        cout << n << "\t\t";
        for(int i =0; i < n; i++){
            array[i]=rand()%1000;
        }


        //quick sort
        begin=clock();
        quicksort(array,0,n);
        end=clock();
        cout << diffclock(end,begin) << "\t";

    }

    return 0;
}
