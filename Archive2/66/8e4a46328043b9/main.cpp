#include <thread>

struct Foo
{
    Foo()
    {
        constexpr int p = 5;
        std::thread threads[p];
        for (int i = 0; i < p - 1; ++i)
            threads[i] = std::thread(std::bind(&Foo::bar, this));
        
        for (auto& th : threads) th.join();
    }
    
    void bar() {}
};

int main() {}
