#include <iostream>
#include <thread>

int n1 = 0;
int n2 = 0;
struct func
{
    
    func() { n1++;}
    func(const func& _f) { n2++;}

    void operator()() {}
};

int main()
{
    func f;
    std::thread t{ f };
    t.join();
    
    std::cout<<n1<<std::endl;
    std::cout<<n2<<std::endl;

    return 0;
}