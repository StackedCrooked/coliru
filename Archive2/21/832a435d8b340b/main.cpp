#include <iostream>
#include "/Archive2/f8/481edd0d5b02a6/main.cpp" // my_item.hpp

int main() {
    Item my_item("some name", 42);
    std::cout << my_item.name() << ' ' << my_item.value() << '\n';
}