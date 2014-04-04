#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <algorithm>

void f(int& i) { std::cout << "Thread " << i << '\n'; }

int main()
{
    std::vector<std::thread> v;
    for( int i = 0; i < 10; ++i )
    {
        auto t = std::thread(f, i);
        v.push_back(std::move(t));
        assert(!t.joinable());
    }
    std::cout << "main\n";
    std::for_each(v.begin(), v.end(), [](std::thread& t)
    {
        assert(t.joinable());
        t.join();
    });
}