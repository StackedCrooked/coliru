#include <thread>

struct X
{
    void foo()
    {
        auto f = [] (X*, int, double) { };
        
        auto t = std::thread{f, 42, 3.14};
        
        t.join();
    }
};

int main()
{
} 