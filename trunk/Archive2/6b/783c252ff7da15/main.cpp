#include <utility>
#include <iostream>
struct Bob
{
    Bob(){ std::cout << "default constructor" << std::endl;}
    Bob(const Bob &){ std::cout << "copy constructor"<<std::endl;}
    Bob(Bob &&){ std::cout<< "move constructor" << std::endl;}
    
    Bob& operator=(const Bob& other){ std::cout<< " copy assignment" << std::endl; return *this;}
    Bob& operator=(Bob&& other){ std::cout << "move assignment"<<std::endl ; return *this;}
};
void foo(const Bob &b)
{
    std::cout << "foo that takes a lvalue reference" << std::endl;
    Bob a(b);
}
void foo( Bob&& b)
{
    std::cout << "foo that take a rvalue reference" << std::endl;
    Bob a(b);
}
template <typename T>
void foo_template(T&& b)
{
    std::cout << " foo template " << std::endl;
    Bob a(std::forward<T>(b));
}
Bob bar()
{
    Bob b;
    return b;
}
int main()
{
    Bob b;
    
    Bob& lvalue_b = b;
    
    //Bob&& rvalue_b = b // NO !
    Bob&& rvalue_b = std::move(b);
    Bob&& rvalue_b2 = bar();
    
    foo_template(lvalue_b); // T = Bob&
    
    foo_template(std::move(lvalue_b)); // T = Bob&&
    
    foo(bar());
    
    foo(std::move(lvalue_b));
    
    Bob uncle;
    uncle = bar();
    
    
}
