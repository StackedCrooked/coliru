#include <cstdlib>
#include <iostream>
 
int main()
{
    // Allocate an array of 4 integers
    int *array = static_cast<int *>(std::malloc(4 * sizeof(int)));
 
    if (array != nullptr) {
        for (int arrayIdx = 0; arrayIdx < 4; ++arrayIdx) {
            array[arrayIdx] = 2 * ( arrayIdx + 1 );
        }
 
        for (int arrayIdx = 0; arrayIdx < 4; ++arrayIdx) {
            std::cout << "Array item " << ( arrayIdx + 1 ) << " = " << array[arrayIdx] << '\n';
        }
        std::free(array);
    }
}