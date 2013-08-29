#include <mutex>
#include <stdio.h>

int main()
{
    std::mutex m;
    puts("before");
    m.lock();
    puts("locked");
    m.unlock();
    puts("after");
}