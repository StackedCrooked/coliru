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
    std::future<std::future<int>> f1 = std::async([]{return std::async([]{ return 1; }); });
    std::future<int> f2 = join(move(f1));
    std::cout << f2.get();
}