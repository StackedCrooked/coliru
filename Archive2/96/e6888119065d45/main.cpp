#include <cstdint>
using namespace std;

volatile uint8_t* array[16];

    void processArray(const volatile uint8_t** inputArray) //<--- ????
    {
        // process each element in the array
    }

    int main()
    {
         processArray(array);// <-- ???
    }
    