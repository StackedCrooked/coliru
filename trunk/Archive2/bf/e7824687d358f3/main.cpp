#include <string>
#include <vector>
#include <sstream>
#include <iostream>

int main()
{
    std::vector<int> v(65536); // az unsigned short altalaban 16 bites; max. erteke 65535
    for (unsigned short i = 0; i < v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    
    return 0;
}

