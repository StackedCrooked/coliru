#include <future>
#include <iostream>
#include <functional>

template<typename T>
std::future<T> join(std::future<std::future<T>>&& f)
{
    struct{
        decltype(f) _f;
        decltype(_f.get().get()) operator()(){
            return _f.get().get();
        }
    } _ { std::move(f) };
    return std::async(_);
}


int main()
{
    std::future<std::future<int>> f1 = std::async([]{return std::async([]{ return 1; }); });
    std::future<int> f2 = join(move(f1));
    std::cout << f2.get();
}