
#include <iostream>
#include <stdint.h>

using namespace std;

int* BinarySearch(int* values, size_t count, int itemToFind){
    bool found = false;
    size_t dicho = count/2;
    size_t gap = count - count/2;

    while(!found || gap > 1){
        if (values[dicho] == itemToFind){
            found = true;
            cout<<"item is found"<<endl;
            return &values[dicho];
            break;
        }
        else if (values[dicho] > itemToFind){
            cout<<"values[dicho]"<<values[dicho]<<endl;
            gap = dicho - dicho/2;
            dicho =  dicho/2;
            cout<<"gap"<<gap<<endl;
            cout<<"dicho"<<dicho<<endl;
        }
        else if (values[dicho] < itemToFind){
            gap = dicho/2;
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
    int tab[] = {1, 2, 3, 4, 5, 6, 7};
    std::cout << *BinarySearch(tab, 7, 7) << std::endl;
    
    return 0;    
}