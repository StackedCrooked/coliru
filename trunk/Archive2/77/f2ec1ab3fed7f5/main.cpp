#include <array>
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>

template<std::size_t N>
void populateArray(std::array<int, N>& array) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<> dist(1, N);
    std::generate_n(array.begin(), N, [&dist, &generator](){ 
        return dist(generator); 
    });
}

int main() {
    std::array<int, 50> array;
    populateArray(array);
    std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
}