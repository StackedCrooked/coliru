#include <cstdlib>
#include <iostream>
#include <utility>


int main () {
    std::srand(7);
    auto seed = std::rand();
    std::srand(seed);
    std::cout << rand() << "\n";
    std::srand(7);
    std::rand();
    std::cout << std::rand();
    }

    