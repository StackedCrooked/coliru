#include <memory>

class A
{
    public:
    
    template<class T>
    class B  { };
};

int main()
{
    A a;
    
    decltype(a)::B b;
}