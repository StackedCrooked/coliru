#include <iostream>
#include <string>
#include <vector>


void fillArray(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        array[i] = i * 3 + 2;
    }
}

int main() {
    int myArray[10];
    
    fillArray(myArray, 11);
    
    std::cout << "Done...\n";
    
    return 0;
}
