#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <atomic>
#include <unistd.h>
#include <math.h>


uint8_t Cipher(uint8_t x)
{
    uint8_t test = 90;
	return ((~test ^ x) << 4) | ((~test ^ x) >> 4);
}
 
int main()
{
    for (int i=0; i<256; ++i)
    {
        if (Cipher(i) == 47)
            std::cout << i << std::endl;
    }
    
    return 0;
}