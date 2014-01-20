#include <thread>

void foo()
{
    while (true)
    {
    }
}

int main()
{
    std::thread a(foo);
    a.detach();
    a = std::thread(foo);
    a.join();
}   