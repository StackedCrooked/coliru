#include <iostream>

namespace B{
struct A;
}

namespace B
{
    struct A
    {
    private:
        int a;
    public:
        A() : a(10){ }
        friend void foo(A * a);
    };
    
    void foo(A* a)
    {
        std::cout << a -> a << std::endl;
    }
}

B::A* a = new B::A;

int main()
{
    foo(a);
}