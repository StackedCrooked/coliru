#include <iostream>
#include <string>
#include <functional>


template <typename T>
struct MyStruct_type {
    
    std::function<bool(T)> someFunc;
    
    MyStruct_type(std::function<bool(T)> someFunc) : someFunc(someFunc) {}; 
};

template <typename T>
MyStruct_type<T> MyStruct(std::function<bool(T)> someFunc) {
    return { someFunc };
};



int main()
{
    
    /* * /
    MyStruct<double>([&](double a) {
        return a > 1;
    });
    /* */
    
    /* */
    MyStruct([&](double a) {
        return a > 1;
    });
    /* */
    
    std::cout << "asdf" << std::endl;
}