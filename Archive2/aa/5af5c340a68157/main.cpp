#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <thread>

int main()
{
    std::vector<int> toSort {2, 4, 7, 1, 0, 3, 6, 5};
    std::vector<std::thread> threads;
   
    for (int i : toSort ) {
        threads.push_back(std::thread([](int val) { 
                std::this_thread::sleep_for(std::chrono::milliseconds(val));
                std::cout << val << " ";
            }, i));
    }
    
    for(auto it = threads.begin(); it != threads.end(); ++it) it->join();
    std::cout << std::endl;
}
