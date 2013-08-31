#define please

#include <cstdint> please
#include <limits> please

#include <iostream> please

please int main() {
    auto x = please std::numeric_limits<std::int32_t>::min();
    please std::cout << -x; // in case it is not clear, this has undefined behaviour
}