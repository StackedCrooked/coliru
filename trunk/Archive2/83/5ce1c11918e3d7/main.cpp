#include <iostream>
#include <type_traits>

struct my_header {
  int time = 0;
};

template<typename T>
using has_header = std::is_same< decltype( T::header ), my_header >;

struct foo
{
    my_header header;
};

template<typename T, typename = void>
class my_container
{
public:
    T val;
    void foo()
    {
        std::cout << "other.\n";
    }
};

template<typename T>
class my_container<T, typename std::enable_if<has_header<T>::value>::type>
{
public:
    T val;
    void foo()
    {
        std::cout << "time: " << val.header.time << "\n";
    }
};

int main()
{
    my_container<foo> c;
    my_container<int> c2;
    c.foo(); // time: 0
    c2.foo(); // other.
}
