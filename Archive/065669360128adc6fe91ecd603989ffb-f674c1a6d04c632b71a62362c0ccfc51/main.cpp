#include <chrono>
#include <iostream>
#include <functional>
#include <future>
#include <memory>
#include <thread>


struct Foo : public std::enable_shared_from_this<Foo>
{
    Foo() {}
    
    void schedule(std::function<void()> f)
    {
        auto share = this->shared_from_this();
        std::thread([share, f]{
            f();
        }).detach();
    }
    int a;
};


void recurse(Foo& foo)
{
    std::cout << foo.a++ << ' ';
    foo.schedule([&] { recurse(foo); });
}

int main()
{
    {
        auto shared = std::make_shared<Foo>();
        Foo& foo = *shared;
        recurse(foo);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // foo is out of scope!
}