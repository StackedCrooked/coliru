#include <chrono>
#include <iostream>
#include <unistd.h>


using namespace std::chrono;


int main(int argc, char** argv)
{
    auto us = strtol(argv[1], NULL, 10);
    
    auto max = 1000;
    auto start = high_resolution_clock::now();
    
    for (int i = 0; i != max; ++i)
    {
        usleep(us);
    }
    
    auto elapsed_us = duration_cast<microseconds>(high_resolution_clock::now() - start).count();
    auto per_iteration = elapsed_us / max;
    std::cout << "usleep(" << us << ") -> " << per_iteration << " us\n";
}