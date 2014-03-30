#include <iostream>
#include <thread>

class A
{
    public:
    void operator()() const { std::cout << 'A' << '\n'; }
};

int main()
{
    std::thread t(A{});
    t.detach();
}