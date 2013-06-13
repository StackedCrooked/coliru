#include <iostream>


int main() {
    int&& iref = 1234;
    std::cout << iref << std::endl;
    
    ++iref;
    std::cout << iref << std::endl;
}