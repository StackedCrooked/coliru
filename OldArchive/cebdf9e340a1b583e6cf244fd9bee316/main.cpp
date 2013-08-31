
#ifndef _SWAP_H
#define _SWAP_H

/** Swaps two items.
 * @pre x and y are the items to be swapped.
 * @post Contents of actual locations that x and y represent are
 *       swapped.
 * @param x  Given data item.
 * @param y  Given data item. */
void swap(int& x, int& y){
   int temp = x;
   x = y;
   y = temp;
}  // end swap

#endif /* _SWAP_H */


/** Chooses a pivot for quicksort's partition algorithm and swaps
 *  it with the first item in an array.
 * @pre theArray[first..last] is an array; first <= last.
 * @post theArray[first] is the pivot.
 * @param theArray  The given array.
 * @param first  The first element to consider in theArray.
 * @param last  The last element to consider in theArray. */
void choosePivot(int theArray[], int first, int last){
    //cerr << "choosePivot(array, " << first << ", " << last << ")\n";
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
}


/** Partitions an array for quicksort.
 * @pre theArray[first..last] is an array; first <= last.
 * @post Partitions theArray[first..last] such that:
 *    S1 = theArray[first..pivotIndex-1] <  pivot
 *         theArray[pivotIndex]          == pivot
 *    S2 = theArray[pivotIndex+1..last]  >= pivot
 * @param theArray  The given array.
 * @param first  The first element to consider in theArray.
 * @param last  The last element to consider in theArray.
 * @param pivotIndex  The index of the pivot after partitioning. */
void partition(int theArray[],
               int first, int last, int& pivotIndex){
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
      }  // end if

      // else item from unknown belongs in S2
   }  // end for

   // place pivot in proper position and mark its location
   swap(theArray[first], theArray[lastS1]);
   pivotIndex = lastS1;
}  // end partition

/** sorts the items in an array into ascending order.
 * @pre theArray[first..last] is an array.
 * @post theArray[first..last] is sorted.
 * @param theArray  The given array.
 * @param first  The first element to consider in theArray.
 * @param last  The last element to consider in theArray. */
void quicksort(int theArray[], int first, int last){
    int pivotIndex;

   if (first < last)
   {  // create the partition: S1, pivot, S2
      partition(theArray, first, last, pivotIndex);

      // sort regions S1 and S2
      quicksort(theArray, first, pivotIndex-1);
      quicksort(theArray, pivotIndex+1, last);
   }  // end if
}  // end quicksort


using namespace std;

#include <ctime>
#include <algorithm>
#include <cassert>
#include <iostream>

void accuracy_test() {    
    {int array[3] = {0,0,0}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {0,0,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {0,1,0}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {1,0,0}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {0,1,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {1,0,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {1,1,0}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {1,1,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {0,1,2}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {0,2,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {1,0,2}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {1,2,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {2,0,1}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
    {int array[3] = {2,1,0}; quicksort(array, 0, 3); assert(std::is_sorted(array, array+3));}
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
