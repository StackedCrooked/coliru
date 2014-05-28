#include <functional>
struct A
{
    explicit A(){};
    explicit A(const A& a){};   
};
A f()
{
    A a;
    return {};
    
}
int main()
{
    A a;
    A b(a);
    
}