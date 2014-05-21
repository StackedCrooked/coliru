#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>


std::atomic<uint64_t> n[100];




int main()
{
    // indices to increment
    enum { i = 6, j = 7, k = 8 };
    
    // the ready flag
    std::atomic<int> r(0);
    
    // start the threads. each thread waits until all other threads are ready and then they start together.
    std::thread t1([&]{ r++; while (r != 3); while (r==3) n[i]++; });
    std::thread t2([&]{ r++; while (r != 3); while (r==3) n[j]++; });
    std::thread t3([&]{ r++; while (r != 3); while (r==3) n[k]++; });


    // wait until all threads have started
    while (r != 3);
    
    
    // wait a little
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // tell the threads to stop incrementing
    r = 0;
    
    // wait until threads are finished
    t1.join(), t2.join(), t3.join();    
    
    
    // print the results
    auto print = [](uint64_t n) { std::cout << (n / 1000000) << " million increments" << std::endl; };
    print(n[i]);
    print(n[j]);
    print(n[k]);
}
