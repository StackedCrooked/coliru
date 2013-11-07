#include <string.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>


using std::chrono::microseconds;
using std::chrono::duration_cast;
using hr_clock = std::chrono::high_resolution_clock;


int main()
{
    long size = 2048;
    long iterations = 10000;
    
    auto src = malloc(size);
    memset(src, 0, size);

    auto dst = malloc(size);

    auto start = hr_clock::now();

    for (long i = 0; i != iterations; ++i)
    {
        memcpy(dst, src, size);
    }

    auto us = duration_cast<microseconds>(hr_clock::now() - start).count();
    auto megabyte_per_second = iterations * size / us;

    std::cout << megabyte_per_second << "MB/s" << std::endl;
}