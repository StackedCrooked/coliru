#include <iostream>
#include <thread>

class A
{
    public:
    void operator()() const { for(int i = 0; i < 10000; i++) std::cout << i << '\n'; }
};

int main()
{
    std::thread t(A{});
    
    t.detach();
    std::cout << "main" << '\n';
}