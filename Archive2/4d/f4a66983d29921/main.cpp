#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

struct bool_wrapper
{
    bool_wrapper(bool& b) : b_(&b) {}
    bool *b_;
    
    bool operator()() const noexcept { return *b_; }
};

std::mutex m;
std::condition_variable c;
bool b = true;

void worker()
{
    std::unique_lock<std::mutex> lock(m);
    c.wait(lock, bool_wrapper(b));
}

int main()
{
    std::thread(worker);
}
