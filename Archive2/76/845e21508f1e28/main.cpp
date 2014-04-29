#include <type_traits>

template <class T>
class Base 
{
public:
    ~Base() {
        static_assert(std::is_same<decltype(T::foo(1)), int>::value, "ERROR STRING");
    }
};

class Derived : public Base<Derived>
{
public:
    static int foo(int) { return 42; };
};

Derived d;