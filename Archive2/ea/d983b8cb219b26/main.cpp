#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <cstdint>

int main(int argc, char** argv)
{
    using namespace std::chrono;
    time_point<system_clock> tp0;
    
    std::vector<uint16_t> v(1024*1024*64);
    std::vector<uint16_t> v2;
    
    std::deque<std::vector<uint16_t>> d;
    
    tp0 = system_clock::now();
    d.push_back(v);
    std::cout << "Time 1: " << duration_cast<milliseconds>(system_clock::now() - tp0).count() << "ms\n";
    
    // takes less than 5msec
    tp0 = system_clock::now();
    d.push_back(v2);
    std::cout << "Time 2: " << duration_cast<milliseconds>(system_clock::now() - tp0).count() << "ms\n";
    
    
    tp0 = system_clock::now();
    d.back() = v;
    std::cout << "Time 3: " << duration_cast<milliseconds>(system_clock::now() - tp0).count() << "ms\n";
    
    return 0;
}