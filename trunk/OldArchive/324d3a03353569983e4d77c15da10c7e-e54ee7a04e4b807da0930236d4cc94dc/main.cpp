#include <future>
#include <iostream>


template<typename F>
auto defer(F&& f) -> std::future<decltype(f())>
{
    return std::async(std::launch::deferred, std::forward<F>(f));
}


int main()
{
    defer([]{std::cout << "Deferred." << std::endl;});
}