#include <future>
#include <iostream>
#include <string>
#include <thread>
#include "tbb/concurrent_queue.h"

template<typename Queue>
void split(const std::string & text, const std::string & delim, Queue&& queue)
{
    std::string::size_type begin = 0;
    for (;;)
    {
        std::string::size_type end = text.find(delim, begin);
        if (end == std::string::npos)
        {
            queue.push(text.substr(begin, std::string::npos));
            queue.push(delim); // pushing delim notifies completion..??
            break;
        }

        queue.push(text.substr(begin, end - begin));
        begin = end + delim.size();
    }
}


int main()
{
    // prevent long deadlock while debugging
    std::thread([]{
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::abort();
    }).detach();
    
    
    // the concurent queue
    tbb::concurrent_bounded_queue<std::string> queue;
    
    // launch the split function in a worker thread
    auto fut = std::async(std::launch::async, [&] {
        split("abc-123-def", "-", queue);
    });
    
    // main thread is now the consumer thread for the queue
    for (;;)
    {
        std::string result;
        queue.pop(result);
        
        if (result == "-") // delimiter received means we are done
        {
            break;
        }
        
        std::cout << "got " << result << std::endl;
    }
    
    // wait for the async thread to complete (or throw)
    fut.get();
}