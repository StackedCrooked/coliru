#include <iostream>
#include <vector>
#include <chrono>
 
int main()
{
    for (unsigned long long size = 1; size < 10000000; size *= 10) {
        auto start = std::chrono::steady_clock::now();
        std::vector<int> v(size, 42);
        auto end = std::chrono::steady_clock::now();
 
        auto elapsed = end - start;
        std::cout << size << ": " << elapsed.count() << '\n';
    }
}