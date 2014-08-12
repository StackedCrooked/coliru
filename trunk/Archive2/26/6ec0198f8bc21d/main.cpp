#include <iostream>

void foo(float f) { std::cout << "\nfloat"; }

void foo(double d) { std::cout << "\ndouble"; }

template<typename T>
void bar(T t)
{
      foo(t);
}

int main()
{
    // Comparisons
    float x = 4.2;
    if( x == 4.2)
       std::cout << "oops"; // Not executed !
       
    if( x == 4.2f)
       std::cout << "ok !"; // executed !
       
    // Overloads   
    foo(42.0);
    foo(42.0f);
    
    // auto type deduction
    auto d = 42.0;
    auto f = 42.0f;
    
    foo(d);
    foo(f);
    
    //Template type deduction
    bar(42.0);
    bar(42.0f);
    
    return 0;
}