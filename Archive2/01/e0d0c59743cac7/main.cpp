#include <vector>
#include <iostream>
 
 class A
 {
    struct B
    {
        int fun() { return 42; }
    };
    
    B b;
    
public:

    B& foo()
    {
        return b;
    }  
 };
 
 
int main()
{
    A a;
    std::cout << a.foo().fun() << std::endl;
    
    auto t = a.foo();
    
    std::vector<decltype(t)> vec(5);
    
    std::cout << vec[2].fun() << std::endl;
    
}