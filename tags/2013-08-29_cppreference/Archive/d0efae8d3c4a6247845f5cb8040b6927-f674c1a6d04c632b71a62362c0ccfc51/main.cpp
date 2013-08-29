#include <array>
#include <atomic>
#include <iostream>
#include <thread>
#include <unistd.h>


int Id;
const int Max = 2000000;
const int ThreadCount = 4;
const int MaxThread = Max / ThreadCount;


int main()
{
    auto loop = [=]{
        for (auto i = 0; i != MaxThread; ++i) {   
            // randomize
            if (rand() % 100 == 0) {
                usleep(1); 
            }
            ++Id;
        }
    };
    
    std::array<std::thread, ThreadCount> threads
    {
        std::thread(loop),
        std::thread(loop),
        std::thread(loop),
        std::thread(loop)
    };
    
    for (auto& t : threads)
    {
        t.join();
    }
    
    
    std::cout << "Id=" << Id << std::endl;
    std::cout << "Max=" << Max << std::endl;
    std::cout << "Difference: " << (Max - Id) << std::endl;
}