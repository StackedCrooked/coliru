#include <future>
#include <iostream>


template<typename T>
std::future<T> join(std::future<std::future<T>>&& f)
{
    auto ptr = std::make_shared<std::future<std::future<T>>>(move(f));
    return std::async([=] {
        return ptr->get().get();
    });
}


int main()
{
    std::future<std::future<int>> f1 = std::async([]{return std::async([]{ return 1; }); });
    std::future<int> f2 = join(move(f1));
}