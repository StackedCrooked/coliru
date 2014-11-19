#include <string>
#include <functional>
#include <iostream>

class A
{
public:
    A(std::string s)
        :s_(s)
    {
        std::cout << "A constructed\n";
    }
    ~A()
    {
        std::cout << "A destructed\n";
    }
    A(const A& a)
        :s_(a.s_)
    {
        std::cout << "A copy constructed\n";
    }
    A(A&& a)
       :s_(std::move(a.s_))
    {
        std::cout << "A moved\n";
    }

    std::string s_;
};

int main()
{
    A a("hello ");
    std::function<void()> f = [a]{ std::cout << a.s_; };
    std::function<void()> g(std::move(f));
}