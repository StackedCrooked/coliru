#include <iostream>
#include <future>

struct X {void f() {std::cout << "yay" << std::endl;}}; 
int main() 
{
    X* x = new X; 
    auto foo = std::async(&X::f, x);
    foo.get();
}