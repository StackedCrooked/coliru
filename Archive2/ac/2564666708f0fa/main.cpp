#include <type_traits>
#include <iostream>
#include <unordered_map>

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <math.h>
using namespace std;

#define UL_BANDWIDTH 2

template <typename T> class TD;

double convert_to_linear (uint8_t val)
{
     double step = (20.0 - (-20.0)) / 255.0;
     return pow(10, (-20 + step * val) / 10);
}


int main() {
     uint8_t ul_sinr[UL_BANDWIDTH]={0,127};
     double ul_sinr2[UL_BANDWIDTH];

     for (uint8_t i=0; i< UL_BANDWIDTH ; i++)
     {
         ul_sinr2[i]=convert_to_linear(ul_sinr[i]);
         std::cout << " ul sinr " << ul_sinr2[i] << std::endl;
     }
}

