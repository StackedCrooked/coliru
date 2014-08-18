
#include <iostream>
#include <type_traits>

int main () {
    int i = 7;
    int& ir = i;
    ir = (ir + 3) & ~static_cast<std::remove_reference<decltype(ir)>::type>(3);
    std::cout << ir;
}