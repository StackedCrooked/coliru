#include "/Archive2/b1/a01cab108e93e3/main.cpp" // my_item.hpp
#include <sstream>
#include <iostream>

int main() {
    std::istringstream input("some_item 42");
    Item my_item;
    input >> my_item;
    std::cout << my_item << std::endl;
}