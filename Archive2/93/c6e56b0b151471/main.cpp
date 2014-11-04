#include <iostream>


std::size_t counter = 0;


template<typename T>
std::size_t type_index() {
    static auto index = counter++;
    return index;
}


int main() {
    std::cout << type_index<int>() << std::endl;
    std::cout << type_index<float>() << std::endl;
    std::cout << type_index<decltype(std::cout)>() << std::endl;
}