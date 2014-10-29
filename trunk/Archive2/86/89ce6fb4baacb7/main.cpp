#include <iostream>
class A{
    public:
        A(int p){std::cout << "A ctor\n";}
};

class B{
    public:
        B(int p){std::cout << "B ctor\n";}
};
class C{
public:
    C(int a, int b)
        : m_b(b), m_a(a)
    {std::cout << "C ctor\n";}
private:
        A m_a;
        B m_b;
};

int main()
{
    C(1, 2);    
}