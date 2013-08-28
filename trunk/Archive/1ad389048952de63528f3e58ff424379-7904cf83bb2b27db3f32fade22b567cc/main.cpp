#include <iostream>
#include <functional>
int main()
{
    typedef std::function<void()> fun;
    int value = 0;
    fun f1 = [=]() mutable { std::cout << value++ << '\n'; };
    fun f2 = f1;           // copy or shared state??
    
    f1(); f1(); f1();      // print 0 1 2
    
    f2();                  // if copy -> 0, if shared -> 3
}
