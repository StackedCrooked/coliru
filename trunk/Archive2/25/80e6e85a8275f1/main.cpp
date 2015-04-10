#include <iostream>
#include <functional>
 
struct X {
    int x;
 
    int&       easy()      {return x;}
    int&       get()       {return x;}
    const int& get() const {return x;}
};
 
 
int main(void)
{
    auto a = std::mem_fn        (&X::easy); // no problem at all
//  auto b = std::mem_fn<int&  >(&X::get ); // no longer works in C++14
    auto c = std::mem_fn<int&()>(&X::get ); // works with both C++11 and C++14
    auto d = [] (X& x) {return x.get();};   // another approach to overload resolution
 
    X x = {33};
    std::cout << "a() = " << a(x) << '\n';
    std::cout << "c() = " << c(x) << '\n';
    std::cout << "d() = " << d(x) << '\n';
}