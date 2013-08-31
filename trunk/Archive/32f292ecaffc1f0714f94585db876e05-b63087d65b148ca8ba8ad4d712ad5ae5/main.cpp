#include <iostream>

void bar() 
{ 
    std::cout << __PRETTY_FUNCTION__ << std::endl; 
} 

void (&foo())()
{ 
    return bar; 
}

int main() 
{ 
    void (&f)() = foo(); 
    f();     
}
