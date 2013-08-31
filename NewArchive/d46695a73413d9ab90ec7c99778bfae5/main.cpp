#include <memory>

class A
{
    public:
    
    class B  { };
};

int main()
{
    A a;
    
    decltype(a)::B b;
}