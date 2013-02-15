#include <future>
#include <iostream>

void schedule_function(const std::function<void()>& ) { /*...*/ }

template<typename R>
std::future<R> schedule_function(R (&func)())
{
    std::shared_ptr< std::promise<R> > prom = std::make_shared<std::promise<R> >();
    auto l = [=]() {  prom.set_value(func()); };
    std::function<void()> f = l;
    schedule_function(f);
    return prom->get_future();    
}

template<typename F>
auto schedule_function(const F & f) -> decltype(f())
{
    // ???
}

struct Increment
{
    int operator()(int n) const { return n + 1; }
};

int inc(int n){ return n + 1; }

int main()
{
    std::future<int> n = schedule_function(&inc);
    std::future<int> m = schedule_function(Increment());
    n.wait();
    m.wait();    
}