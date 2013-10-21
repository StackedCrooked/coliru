#include <iostream>

// X.hpp
struct X
{
    template<class T> void fun();
    void gun();
};

// X.cpp
// #include "X.hpp"
template<class T>
void X::fun()  
{ 
    std::cout << "TU1\n"; 
}

void X::gun() 
{ 
    fun<int>(); 
}

/*
// Foo.cpp
// #incluce "X.hpp" 

template<>
void X::fun<int>()
{
    std::cout << "TU2\n";    
}
*/

// main.cpp
// #include "X.hpp"
int main() 
{
    X x;
    x.gun();
}
