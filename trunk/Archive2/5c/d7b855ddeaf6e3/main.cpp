#include <iostream>
#include <string>
#include <utility>
#include <thread>
#include <vector>

struct NotCopyable
{
    NotCopyable() { std::cout << "default constructed\n"; }
    NotCopyable(const NotCopyable&) = delete;
    NotCopyable(NotCopyable&& nc) { std::cout << "move constructed\n"; }
    void a() { };
};

NotCopyable getNC()
{
    return NotCopyable();
}

std::thread getThread()
{
    return std::thread();
}

int main()
{
    std::thread t = getThread();
}
