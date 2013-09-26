#include <iostream>
#include <iterator>
#include <array>
#include <utility>

class Foo
{
private:
    int a_ = 0;
    int b_ = 0;
    int c_ = 0;
    int d_ = 0;
    
public:
    constexpr Foo() = default;
   
    constexpr Foo(int a, int b, int c, int d)
    : 
        a_{a}, b_{b}, c_{c}, d_{d}
    {}
          
    constexpr Foo& SetA(int i) { a_ = i; return *this; }
    constexpr Foo& SetB(int i) { b_ = i; return *this; }
    constexpr Foo& SetC(int i) { c_ = i; return *this; }
    constexpr Foo& SetD(int i) { d_ = i; return *this; }

    friend std::ostream& operator<<(std::ostream& os, const Foo& f)
    {
        return os << f.a_ << " " << f.b_ << " " << f.c_ << " " << f.d_ << " ";    
    }
};

int main() 
{
    constexpr Foo f = Foo{}.SetB(5).SetA(2);
    std::cout << f;
}
