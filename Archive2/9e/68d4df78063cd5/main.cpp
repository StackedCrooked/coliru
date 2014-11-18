#include <iostream>
#include <vector>
#include <chrono>
 
int main()
{
    for (unsigned long long size = 1; size < 10000000; size *= 10) {
 
        auto start = std::chrono::high_resolution_clock::now();   // a "timepoint" representing now
 
        std::vector<int> v(size, 42);               // something that takes some time to do
 
        auto end = std::chrono::high_resolution_clock::now();     // the new current "timepoint"
 
        auto elapsed = end - start;                 // difference is a "duration"
 
        std::cout << size << ": " << elapsed.count() << '\n';  // clock ticks (seconds)
    }
}