#include <cstdint>
#include <iostream>

template <class... Ts>
std::size_t SizeSum() {
    std::size_t sum = 0u;
    for(std::size_t s : {sizeof(Ts)...})
        sum += s;
    return sum;
}

int main() {
    std::cout << SizeSum<int, float, char, short>() << '\n';
    return 0;
}