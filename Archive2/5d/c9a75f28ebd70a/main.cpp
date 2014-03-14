#include <iostream>
#include <string>
#include <vector>

int main()
{
    const size_t BOARD_DIMENSIONS = 5;
       short** array2d = new short*[BOARD_DIMENSIONS];
    for (size_t u = 0; u < BOARD_DIMENSIONS; ++u)
    {
        array2d[u] = new short[BOARD_DIMENSIONS];
        // You could then use memset to initialize the array, or
        // use a for loop, like in your example:
        for (size_t v = 0; v < BOARD_DIMENSIONS; ++v)
        {
            array2d[u][v] = 0;
        }
     }
     
     for (size_t u = 0; u < BOARD_DIMESIONS; ++u)
     {
        for (size_t v = 0; v < BOARD_DIMENSIONS; ++v)
            printf ("%u - ", array2d[u][v]);
     }
}
