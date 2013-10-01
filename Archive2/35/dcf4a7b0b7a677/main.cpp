#include <iostream>
#include <type_traits>
#include <memory>

template<typename Derived>
struct ImplProvider
{
    ImplProvider()
    {
        static_assert(std::is_base_of<ImplProvider, Derived>::value,
                      "Template parameter must be deriving class");
    }
    
//protected:
//    friend Derived;  // actually legal, see http://stackoverflow.com/a/6510163/420683
    struct Impl;
};

template<class Derived>
struct ptr_provider : private ImplProvider<Derived>, protected std::unique_ptr< typename ImplProvider<Derived>::Impl >
{
    using typename ImplProvider<Derived>::Impl;
    
    ptr_provider(std::unique_ptr<Impl> p)
        : std::unique_ptr<Impl>(std::move(p))
    {
        static_assert(std::is_base_of<ptr_provider, Derived>::value,
                      "Template parameter must be deriving class");
    }
};

struct Test : private ptr_provider<Test>
{
    Test();
    void f();
};

int main()
{
    Test t;
    t.f();
}

template<>
struct ImplProvider<Test>::Impl
{
    Impl()
    {
        std::cout << "It works!" << std::endl;
    }
    int x = 7;
};

Test::Test()
: ptr_provider(std::unique_ptr<Impl>(new Impl)) // make_unique
{
}

void Test::f()
{
    std::cout << (*this)->x << std::endl;
}