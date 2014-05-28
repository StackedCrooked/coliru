#include <functional>
struct A
{
    A(){};
    explicit A(const A& a){};   
};
A f()
{
    A a;
    return {a};
    
}
int main()
{
    A a;
    A b(a);
    
}