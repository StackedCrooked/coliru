#include <iostream>
#include <thread>

struct func
{
    func() = default;
    func(func&&) {std::cout <<"move\n";}
    func(const func&) {std::cout <<"copy\n";}
    void operator()() const {}
};

int main()
{
    func f;
    std::thread{ f }.join();
}
