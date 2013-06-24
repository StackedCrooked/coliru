#include <chrono>
#include <iostream>
#include <functional>
#include <future>
#include <memory>
#include <thread>


struct Foo
{
    Foo() : mCheckLifetime(this, [](Foo*){}), a() {}
    
    void schedule(std::function<void()> f)
    {
        std::weak_ptr<Foo> checkLifetime{mCheckLifetime};
        std::thread([=]{
            if (checkLifetime.expired()) {
                std::cout << "Expired!" << std::endl;
                return;
            }
            f();
        }).detach();
    }
    
    std::shared_ptr<Foo> mCheckLifetime;
    int a;
};


void recurse(Foo& foo)
{
    std::cout << foo.a++ << ' ';
    foo.schedule([&] { recurse(foo); });
};  

int main()
{
    {
        Foo foo;
        recurse(foo);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // foo is out of scope!
}