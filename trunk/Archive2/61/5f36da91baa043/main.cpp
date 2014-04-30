#include <type_traits>

template <class T>
class Base 
{
public:
    ~Base() {
        static_assert(std::is_same<decltype(T::foo(std::declval<int>()), int>::value, "ERROR STRING");
    }
};

class Good : public Base<Good>
{
public:
    static int foo(int) { return 42; };
};

class Bad : public Base<Bad>
{
public:
    static double foo(int) { return 42; };
};

Good g;
Bad b;
