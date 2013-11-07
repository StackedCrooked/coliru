#include <future>
#include <cstdio>

void f() { printf("f()\n"); }
void g() { printf("g()\n"); }

int main()
{
    std::async(std::launch::async, []{ f(); });
    std::async(std::launch::async, []{ g(); });  // does not run until f() completes
}