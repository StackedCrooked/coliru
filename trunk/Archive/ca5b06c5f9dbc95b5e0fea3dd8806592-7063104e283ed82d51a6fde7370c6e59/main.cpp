#include <iostream>
 
struct Helper
{
    Helper() {}
    Helper(const Helper& src) { std::cout << "copy\n"; }
    Helper(Helper&& src)      { std::cout << "move\n"; }
};
 
struct A
{
    virtual ~A() {}
    Helper h;
};
 
struct B
{
    virtual ~B() = default;
    Helper h;
};
 
 
int main()
{
    {
        A x;
        A y(std::move(x));   // outputs "copy", because no move possible
    }
    
    {
        B x;
        B y(std::move(x));   // outputs "copy", because still no move possible
    } 
}