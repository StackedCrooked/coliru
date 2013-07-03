#include <iostream>
#include <thread>
#include <vector>
#include <functional>

void function(const std::vector<double>& datavector)
{
    std::cout << datavector.data() << "\n";
}

int main()
{
    // Create a vector containing 12 elements.
    //
    std::vector<double> data;
    for(uint32_t i = 0x0; i < 0xC; i ++) data.push_back(i % 0x3);

    // Start multiple threads.
    //
    std::vector<std::thread> thread;
    std::vector<double> result;
    result.push_back(0.0);

    thread.push_back(std::thread(function, std::cref(data)));
    thread.push_back(std::thread(function, std::cref(data)));

    // Wait for threads to complete.
    //
    thread[0].join();
    thread[1].join();

    return 0;
}
