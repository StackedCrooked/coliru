#include <future>

template<typename F>
void wait(const F& f)
{
    f.wait();
}

template<typename ...F>
void wait(F&& ...f)
{
    using swallow = int[];
    (void)swallow{(wait(std::forward<F>(f)), 0)...};
}