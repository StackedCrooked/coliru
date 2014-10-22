
#include <iostream>
#include <stdint.h>

using namespace std;

int* BinarySearch(int* values, size_t count, int itemToFind){
    size_t start = 0;
    size_t end = count;
    while (start < end) {
        const size_t current = (end - start) / 2 + start;
        const int value = values[current];
        if (value == itemToFind) {
            return &values[current];
        }
        
        if (itemToFind > value) {
            start = current + 1;
        }
        else {
            end = current;    
        }
    }
    return NULL;
}

int main()
{
    int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << *BinarySearch(tab, 10, 255) << std::endl;
    
    return 0;    
}