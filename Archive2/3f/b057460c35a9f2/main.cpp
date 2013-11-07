#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex gMutex;

void runShit(int x)
{
    std::unique_lock<std::mutex> lock(gMutex);
    std::cout << "Test:" << x << "'s shit" << std::endl;
    return;
}

int main()
{
    std::vector<std::thread> threads;
    for( int i = 0; i < 10; ++i )
    {
        threads.emplace_back(runShit, i);
    }
    
    for( std::thread& x: threads)
        x.join();
    
    return 0;
}