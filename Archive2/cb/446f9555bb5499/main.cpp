#include <iostream>
#include <type_traits>

int main(int argc, char** argv) {
    typename std::common_type<decltype(-1), decltype(1u)>::type x;
    x = -1;
    std::cout << x << "\n";
    return 0;
}