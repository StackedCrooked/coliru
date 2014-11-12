
// g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out

#include <atomic>
#include <chrono>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>


alignas(128) std::atomic<uint64_t> n[100];


void test(int i, int j, int k, int factor)
{
    memset(n, 0, sizeof(n));

    // the ready flag
    auto& r = n[99];
    r = 0;
   
    // start the threads. each thread waits until other threads are ready before it starts incrementing
    std::thread t1([&]{ r++; while (r != 3); while (r==3) n[i]++; });
    std::thread t2([&]{ r++; while (r != 3); while (r==3) n[j]++; });
    std::thread t3([&]{ r++; while (r != 3); while (r==3) n[k]++; });


    // wait until all threads have started
    while (r != 3);
   
   
    // wait a little
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // tell the threads to stop incrementing
    r = 0;
   
    // wait until threads are finished
    t1.join(), t2.join(), t3.join();   
   
   
    // print the results
    //auto print = [=](uint64_t n) {
        //std::cout << n << std::endl;
    //};
    std::cout << i << ',' << j << ',' << k << ": " << n[i]/factor << ' ' << n[j]/factor << ' ' << n[k]/factor << std::endl;
}


int main(int argc, char** argv)
{
    // factor can be used to scale down the counters to make them more readable
    // usage: ./a.out 100 => all numbers are divided by 100
    int factor = 1;
    if (argc > 1) 
    {
        std::istringstream iss(argv[1]);
        iss >> factor;
    }
    test(0, 1, 2, factor);  // ouch 3 threads working on 1 cache line
    test(0, 1, 40, factor);  // 0 and 1 work on the same cache line, index 8 has own cache line
    test(0, 10, 40, factor); // each thread has own cache line
}
