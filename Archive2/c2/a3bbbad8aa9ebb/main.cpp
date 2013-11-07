#include <iostream>
#include <limits>

int main(){
    if (std::numeric_limits<float>::infinity() < 2000)
        std::cout << "lolwut\n";
}