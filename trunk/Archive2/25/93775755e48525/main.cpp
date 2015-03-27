#include <iostream>


template <typename T>
class A
{
public:
    A()
    {}

    template <typename T2>
    A(const A<T2>& rhs)
    {
        std::cout << "template copy ctor" << std::endl;   
    }
    
    template <typename T1>
    A<T>& operator=(const A<T1>&)
    {
        std::cout << "template assignment" << std::endl;
        return *this;
    }
};


class D
{
public:
    virtual void foo(int)
    {
        std::cout << "virtual foo int" << std::endl;
    }
    
    void foo(double)
    {
        std::cout << "foo double" << std::endl;
    }
};

class B : public D
{
public:
    template <typename T>
    void foo(T)
    {
        std::cout << "template function" << std::endl;
    }
};

template <typename T>
void ignore(const T& o)
{
    if (0 == &o) {}
}

int main()
{
    A<int> a;
    A<int> b = a;
    ignore(b);
    A<double> d = b;
    ignore(d);
    a = d;
    a = b;
    
    B z;
    z.foo<int>();
    z.foo<double>();
    
}