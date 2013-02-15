#include <iostream>
#include <algorithm>
#include <cstdlib>

int main()
{
        int numArray[] ={1,4,5,10,11,12,13,14,15,16,17,18,19,20,35,26,43,15,48,69,32,45,57,98,100};
        
        int key = 7;
        auto cmp = [&](int a, int b) { return std::abs(key-a) < std::abs(key-b); };
        int nearest_value = *std::min_element(std::begin(numArray), std::end(numArray), cmp);
        std::cout << nearest_value << std::endl;
}
