#include <iostream>
#include <string>
#include <vector>

template <class T> 
struct Base
{
    void interface()
    {
        // ...
        static_cast<T*>(this)->implementation();
        // ...
    }
 
    static void static_func()
    {
        // ...
        T::static_sub_func();
        // ...
    }
};
 
 
struct Derived : Base<Derived>
{
    void implementation()
    {
        std::cout << "Implementation in Derived\n"; 
    }
    
    static void static_sub_func()
    {
        std::cout << "No object creation is needed\n"; 
    }
};


int main()
{
    // 1. Through member function
    Base<Derived> obj; 
    obj.interface(); 
    // 2. Through non members (no object creation is needed)
    Base<Derived>::static_func();    
}
