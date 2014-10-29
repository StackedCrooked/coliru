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
        C(){std::cout << "C ctor\n";}
};
class D{
    public:
        D(int a, int b)
            : m_b(b), m_a(a)
        {std::cout << "D ctor\n";}
    private:
        A m_a;
        B m_b;
        C m_c;
};

int main()
{
    D(1, 2);    
}