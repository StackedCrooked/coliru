#include <iostream>
#include <array>
#include <algorithm>
#include <atomic>

int main() {

    //std::array<std::atomic<int>, 1000000>  arr;         // default initialization (i.e., random data) = FAST
    //std::array<int, 1000000>  arr={{}};     // zero init non-atomic = FAST
    std::array<std::atomic<int>, 1000000>  arr{{}};   // zero initialization = FOREVER
    std::array<std::atomic<int>, 1000000>  arr2={{}};     // zero init via assignment = FOREVER
    std::array<std::atomic<int>, 1000000>  arr3{};   // zero initialization = FOREVER

    std::cerr << "sum = " << std::accumulate(arr.begin(), arr.end(), 0) << std::endl;
}
