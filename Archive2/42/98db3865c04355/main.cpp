#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <boost/thread.hpp>
#include <vector>
#include <functional>

namespace NS = boost;

static NS::mutex mtx;
NS::unique_lock<NS::mutex> lock() {
    return NS::unique_lock<NS::mutex>{mtx};
}

int main()
{
    std::vector<std::function<void()>> messages;
    NS::atomic<bool> running{true};

    NS::thread thread([&]{
        while (running) {
            std::vector<std::function<void()>> own;
            {
                //auto lk = lock();
                NS::lock_guard<NS::mutex> lk(mtx);
                own.swap(messages);
            }
            std::cout << "[T] locked with " << own.size() << " messages." << std::endl;
            for (auto& fn: own) {
                fn();
            }   
        }   
    }); 

    for (int i = 0; i < 1000000; ++i) {
        NS::packaged_task<int> task([=]{
            std::cout << "[T] returning " << i << std::endl;
            return i;
        }); 

        {   
            //auto lk = lock();
            NS::lock_guard<NS::mutex> lk(mtx);
            messages.emplace_back(std::bind(std::ref(task)));
        }   

        task.get_future().get();
    }   

    running = false;
    thread.join();
}
