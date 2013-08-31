#include <iostream>
#include <boost/type_traits/is_same.hpp>

typedef int type1;
typedef float type2;

template <typename T>
class Foo
{
    public:
        typedef T type_t;

        virtual double compute() { return 1.0; }
};

template <typename T>
class FooDerived
{
    public:
        typedef T type_t;

        double compute() { return 42.0; }
};

template <class T>
class Bar : public T
{
public:
    void f()
    {
        // types have to be known...
        if (boost::is_same<typename T::type_t, type1>::value)
            std::cout << "Bar< T<type1> > : " << this->compute() << std::endl;
        else if (boost::is_same<typename T::type_t, type2>::value)
            std::cout << "Bar< T<type2> > : " << this->compute() << std::endl;
    }
};

int main(void)
{
    Bar< Foo<type1> > a;
    a.f();
    Bar< FooDerived<type2> > b;
    b.f();
}