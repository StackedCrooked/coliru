#include <thread>
#include <iostream>

class Foo
{
    Foo(int n = 10)
    {
        size_t a[n];
        constexpr int p = 5;
        std::thread threads[p];
        for (int i = 0; i < p - 1; ++i)
            threads[i] = std::thread(std::bind(&Foo::bar, this, a, n));
        
        for (auto& th : threads) th.join();
    }
    
    void bar(size_t* a, int n) {}
};

int main() {std::cout << "ok\n";}
