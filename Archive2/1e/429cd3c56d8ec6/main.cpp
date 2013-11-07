#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex gMutex;

int main()
{
    std::vector<std::thread> threads;
    for( int i = 0; i < 10; ++i )
    {
        threads.emplace_back([&]{
            std::unique_lock<std::mutex> lock(gMutex);
            std::cout << "this is shit." << std::endl;
            lock.unlock();
            
            return;
        });
    }
    
    return 0;
}