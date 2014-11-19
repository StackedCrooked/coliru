#include <string>
#include <functional>
#include <iostream>

class A
{
public:
    A(std::string s) :s_(s) { std::cout << "A conv ctor\n"; }
    ~A() {std::cout << "A dtor\n";}
    A(const A& a):s_(a.s_) {std::cout << "A copy ctor\n";}
    A(A&& a):s_(std::move(a.s_)) {std::cout << "A move ctor\n";}
    A&operator=(const A& a){s_=a.s_; std::cout << "A copy assn\n";return *this;}
    A&operator=(A&& a) {s_=std::move(a.s_); std::cout << "A move assn\n";return *this;}
    std::string s_;
};

int main()
{
    A a("hello ");
    std::cout << "before lambda\n";
    auto&& lambda = [a]{ std::cout << a.s_; };
    std::cout << "before lambda+function\n";
    std::function<void()> f = [a]{ std::cout << a.s_; };
    std::cout << "before move function\n";    
    std::function<void()> g(std::move(f));
    std::cout << "before end of scope\n";
}