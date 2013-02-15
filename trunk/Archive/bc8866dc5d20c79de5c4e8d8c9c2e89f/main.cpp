#include "Poco/Stopwatch.h"
#include "tbb/concurrent_queue.h"
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <thread>


void testPoco()
{    
    Poco::Stopwatch s;
    s.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "Poco::Stopwatch: elapsed " << s.elapsed() << " microseconds" << std::endl;
}

void testTBB()
{    
    tbb::strict_ppl::concurrent_queue<int> queue;
    queue.push(1);    
    int n = 0;    
    if (queue.try_pop(n))
    {
        std::cout << "Intel Threading Building Blocks: concurrent_queue popped " << n << std::endl;
    }
}

int main()
{
    testPoco();
    testTBB();
}

