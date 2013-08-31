#include <future>
#include <iostream>


template<typename T>
std::future<T> join(std::future<std::future<T>>&& f)
{
    std::shared_future<std::future<T>> shared(std::move(f));
    return std::async([=] {
        std::future<T> inner = shared.get();
        return inner.get();
    });
}


int main()
{
    std::future<std::future<int>> f1 = std::async([]{return std::async([]{ return 1; }); });
    std::future<int> f2 = join(move(f1));
}