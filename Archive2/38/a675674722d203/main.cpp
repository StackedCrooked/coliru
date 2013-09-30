#include <iostream>

struct demo
{
    demo(demo const & ) { std::cout << "copy constructor." << std::endl; }
    
    template<typename T> 
    demo(T &&) { std::cout << "template constructor." << std::endl; }
    
};

int main()
{
    demo x{10};
    demo y(x);
}
