#include <atomic>
#include <mutex>
#include <iostream>
#include <thread>


std::mutex m;

long sane_thread_id()
{
    static std::atomic<long> counter{0};
    static __thread const long id = counter++;
    return id;
}


int main()
{
    auto p = []{
        std::lock_guard<std::mutex> lock(m);
        std::cout << "insane=" << std::this_thread::get_id() << ", sane=" << sane_thread_id() << '\n';
    };
    
    std::thread t1(p), t2(p), t3(p), t4(p);
                
    t1.join(), t2.join(), t3.join(), t4.join();
}
