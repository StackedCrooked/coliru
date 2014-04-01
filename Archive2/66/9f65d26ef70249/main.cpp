#include <iostream>
#include <thread>
#include <unistd.h>

class A
{
    public:
    void operator()() const { usleep(1); for(int i = 0; i < 10; i++) std::cout << 'A' << '\n'; }
};

int main()
{
    std::thread t(A{});
    
    t.detach();
    std::cout << "main" << '\n';
}