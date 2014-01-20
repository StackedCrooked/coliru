#include <iostream>
#include <initializer_list>


struct A {
    A& operator= (const A&)
    {
        std::cout << "operator= (A&&) " << std::endl ;
        return *this;
    }
    
    A& operator= (A&&)
    {
        std::cout << "operator= (A&&) " << std::endl ;
        return *this;
    }
    
    A& operator= (std::initializer_list<int>)
    {
        std::cout << "operator= (std::initializer_list<int>) " << std::endl ;
        return *this;
    }
};

int main()
{
    A a;
    a = { };
}