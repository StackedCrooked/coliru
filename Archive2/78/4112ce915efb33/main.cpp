#include <iostream>
#include <thread>
#include <vector>

void f()
{
    std::cerr << 'f';
}
void g()
{
    std::cerr << 'g';
}
void fg()
{
    f();
    g();
}
void gf()
{
    g();
    f();
}

int main()
{
    std::vector<std::thread> threads;
    threads.emplace_back(fg);
    threads.emplace_back(gf);
    for(auto &t : threads)
    {
        t.join();
    }
}
