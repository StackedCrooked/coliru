#include <mutex>
#include <stdio.h>

int main()
{
    std::mutex m;
    puts("before");
    puts("locked");
    puts("after");
}