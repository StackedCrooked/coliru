/*  Bubble Sort demonstration
 */
 
#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int main() {
 
    int a, b, t;    // initialise loop counters
    int list[10];   // initialise integer array
    int size = 10;  // size of the array to be sorted
 
    srand(time(0)); // generate rand() seed//<------------changed seed

    for(t = 0; t < size; t++) {   // load array with random numbers
        list[t] = rand() % 10000;
    }
 
    // print the original array
    cout << "\n   **** Orginal Array ****\n";
    cout << "  - ";
    for(t = 0; t < size; t++) {
        cout << list[t] << " - ";
    }
    cout << "\n\n";
 
    // this is Bubble Sort
    for(a = 0; a < size; a++) {
        for(b = size-1; b > a; b--) {//<--------------------changed from b>=a
            if(list[b-1] > list[b]) {   // if out of order
                // exchange elements
                t = list[b-1];
                list[b-1] = list[b];
                list[b] = t;
            }
        }
    }
 
    // print the sorted array
    cout << "   **** Sorted Array *****\n";
    cout << "  - ";
    for(t = 0; t < size; t++){
        cout << list[t] << " - ";
    }
    cout << "\n";
    return 0;
}