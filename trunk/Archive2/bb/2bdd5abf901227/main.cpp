#include <string>
#include <vector>
#include <thread>
#include <future>

struct foo
{
    std::promise<void> p;
    
    foo(std::promise<void> p) : p(std::move(p)) {}
    
    foo(foo&&) = default;
    foo & operator=(foo&&) = default;
    
    void operator()() {}
};

int main()
{
    std::promise<void> p;
    std::future<void> f = p.get_future();
    std::function<void()> fun(foo(std::move(p)));
}
