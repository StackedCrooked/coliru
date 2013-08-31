#include <future>
#include <iostream>
#include <functional>

template<typename T>
std::future<T> join(std::future<std::future<T>> f)
{
    struct joiner{
        decltype(f) _f;
        decltype(_f.get().get()) operator()(){
            return _f.get().get();
        }
    };
    return std::async(std::launch::deferred, joiner{ std::move(f) });
}


int main()
{
    auto f = join(std::async([]{return std::async([]{ return; }); }));
    f.get();
}