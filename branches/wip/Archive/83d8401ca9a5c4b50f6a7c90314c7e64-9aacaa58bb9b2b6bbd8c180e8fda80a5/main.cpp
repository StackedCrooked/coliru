#include <future>

template<typename F>
void wait(const F& f)
{
    f.wait();
}

template<typename ...F>
void wait(F&& ...f)
{
    wait(std::forward<F>(f))...;
}