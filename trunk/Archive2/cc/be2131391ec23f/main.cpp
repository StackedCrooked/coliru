#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
#include <future>

class L
{
public:
    L() { std::cout << "it default constructed" << std::endl; }
    L(L const& r) { std::cout << "it copied" << std::endl; }
    L(L&& r) { std::cout << "it moved!" << std::endl; }
    L& operator=(L const& r) { std::cout << "it assigned" << std::endl; return *this; }
    L& operator=(L&& r) { std::cout << "it move assigned!" << std::endl; return *this; }
    void operator()() { std::cout << "it got called" << std::endl; }
};

template<typename T, typename U>
void dostuff(T&& work, U&& callback)
{
    std::cout << "calling async" << std::endl;
    std::async([work, callback]() {
        work();
        callback();
    });
}

int main()
{
    L a;
    std::cout << "calling dostuff" << std::endl;
    dostuff([a]() { std::cout << "worker work" << std::endl; }, []() { std::cout << "work complete" << std::endl; });
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
