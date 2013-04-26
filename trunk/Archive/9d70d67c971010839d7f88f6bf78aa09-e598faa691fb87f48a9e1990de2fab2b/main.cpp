#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>

struct foo
{
    foo() : b()
    {
        assert(!b);
        std::thread t1([&](){
            if (time(nullptr)%2) b = !b;
        });
        std::thread t2([&](){
            if (time(nullptr)%2) b = !b;
        });
        std::thread t3([&](){
            if (time(nullptr)%2) b = !b;
        });
        std::cout << b;
        t1.join(); t2.join(); t3.join();
    }
    std::atomic<bool> b;
};

int main()
{
    for (int i = 0; i != 100; ++i)
    {
        try
        {
            foo f;
            std::cout << f.b;
        }
        catch (const std::exception& exc)
        {
            std::cerr << exc.what() << std::endl;
        }
    }
}