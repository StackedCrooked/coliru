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
    
    std::cout << "size of std::function<void()> " << sizeof(fun) << '\n';
    std::cout << "size of f1 " << sizeof f1 << '\n';
    int value2 = 2, value3 = 3, value4 = 4, value5 = 5, value6 = 6, value7 = 7;
    f1 = [=](){ std::cout << value << value2 << value3 << value4 << value5
                          << value6 << value7 << '\n'; };
    std::cout << "size of f1 " << sizeof f1 << '\n';
}
