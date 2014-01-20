#include <future>
#include <iostream>

int main()
{
    std::shared_future<int> fut = std::async(std::launch::async, []{ return 1; });
    auto f1 = std::async(std::launch::async, [=]{ return fut.get(); });
    auto f2 = std::async(std::launch::async, [=]{ return fut.get(); });
    auto f3 = std::async(std::launch::async, [=]{ return fut.get(); });
    std::cout << f1.get() << f2.get() << f3.get() << std::endl;
}