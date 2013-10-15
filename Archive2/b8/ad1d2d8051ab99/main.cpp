#include <iostream>
#include <typeinfo>
#include <functional>
#include <type_traits>
#include <chrono>

using namespace std::chrono;

int main()
{     
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << ", s" << i << j << "s(" << i << j << ")"; 
        }    
        std::cout << "\n";
    }
    return 0;
}