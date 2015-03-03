#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <cmath>

int combine(int a, int b) 
{
    int times = 1;
    if( b != 0 )
    {
        times = (int)pow(10.0, (double)((int)log10((double)b)) + 1.0);
    }
    return a * times + b ;
}


int main()
{
    int typ= 12;
    uint32_t sensorId = 4294967;
    int combined = combine (sensorId,typ);
    
    std::cout << combined;
}

