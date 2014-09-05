#include <iostream>

template<typename DerivedT, typename... ParentT>
struct Middle;
template<typename DerivedT, template<typename...> class InheriterT, typename... ParentT>
struct Middle<DerivedT, InheriterT<ParentT...>>
: InheriterT<ParentT...>
{
    void test()
    {
        std::cout << "it works" << std::endl;
    }
};
template<typename... Args>
struct DefaultInheriter
: virtual Args...
{
};
template<typename DerivedT, typename... ParentT>
struct Middle
: Middle<DerivedT, DefaultInheriter<ParentT...>>
{
};

struct Base
: Middle<Base>
{
    virtual ~Base() = default;

    virtual Base *f() const = 0;
};

struct A
: Middle<A, Base>
{
    virtual A *f() const override = 0;
};
struct B
: Middle<B, Base>
{
    virtual B *f() const override = 0;
};

template<typename... Args>
struct ABInheriter
: virtual Args...
{
    virtual ABInheriter *f() const override = 0;
};
struct Derived
: Middle<Derived, ABInheriter<A, B>>
{
    virtual Derived *f() const override = 0;
};

int main()
{
    struct Test
    : Middle<Test, Derived>
    {
        virtual Test *f() const override
        {
            return nullptr;
        }
    } t;
    t.test();
}
