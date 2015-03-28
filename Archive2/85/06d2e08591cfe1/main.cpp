#include <iostream>
#include <string>
#include <vector>

struct Bar
{
    typedef double internalType;  
};

template <typename T> typename T::internalType foo(const T& t) { std::cout << "foo<T>" << std::endl; return 0; }

int main()
{
    foo(Bar());
    foo(0);
}
