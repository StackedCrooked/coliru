#include <future>
#include <iostream>

template<typename T>
static std::future<T> flatten(std::future<T>&& fut)
{
    std::cout << "Last flatten" << std::endl;
    return std::move(fut);
}

template<typename T>
static std::future<T> flatten(std::future<std::future<T>>&& fut)
{
    std::cout << "Flatten" << std::endl;
    return flatten(fut.get());
}


int main()
{
    flatten(std::async([]{ return std::async([]{ return std::async([]{ return std::async([]{ return std::async([]{ return std::async([]{});});});});});}));
}