#include <future>

template<typename... T> void expand(T... t) {}

template<typename F>
char wait(const F& f)
{
    f.wait();
    return 0;
}

template<typename ...F>
void wait(F&& ...f)
{
    expand(wait(std::forward<F>(f))...);
}