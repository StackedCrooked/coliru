
#include <iostream>
#include <stdint.h>

using namespace std;

int* BinarySearch(int* values, size_t count, int itemToFind){
    size_t dicho = count/2;
    size_t gap = count - count/2;

    while(gap > 0){
        if (values[dicho] == itemToFind){
            cout<<"item is found"<<endl;
            return &values[dicho];
        }
        else if (values[dicho] > itemToFind) {
            cout<<"values[dicho]"<<values[dicho]<<endl;
            gap = gap/2;
            dicho =  dicho/2;
            cout<<"gap"<<gap<<endl;
            cout<<"dicho"<<dicho<<endl;
        }
        else if (values[dicho] < itemToFind) {
            gap = gap/2;
            dicho = dicho + dicho/2;
            cout<<"gap"<<gap<<endl;
            cout<<"dicho"<<dicho<<endl;
        }
    }
    cout<<"item not found"<<endl;
    return NULL;
}

int main()
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << *BinarySearch(tab, 10, 525) << std::endl;
    
    return 0;    
}