#include <iostream>
#include <memory>
#include <thread>

struct Foo { void bar() { std::cout << "Foo\n"; } };

int main()
{
    auto p = std::make_shared<Foo>();
    std::thread t1(&Foo::bar, p);
    std::thread t2(&Foo::bar, *p);
    std::thread t3(&Foo::bar, p.get());
    t1.join();
    t2.join();
    t3.join();
}
