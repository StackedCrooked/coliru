#include <thread>
#include <future>
#include <chrono>

void sleep_some() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

std::future<int> do_some_work() {
    std::packaged_task<int()> p([] { sleep_some(); return 42; });
    auto ret_fut = p.get_future();
    
    std::thread t(std::move(p));
    t.detach();
    
    return ret_fut;
}


int main()
{
    // not gonna block
    std::future<int> fut = do_some_work();
}
