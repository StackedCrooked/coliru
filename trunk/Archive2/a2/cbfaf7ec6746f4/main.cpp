#include <iostream>

template<typename T>
struct is_const_reference_type
{
    static const bool value = false;
    typedef T&       reference_type;
    typedef const T& const_reference_type;
};

/*
template<typename T>
struct is_const_reference_type<T&>
{
    static const bool value = false;
    static const int spec = 1;
    typedef T&       reference_type;
    typedef const T& const_reference_type;
};
*/

template<typename T>
struct is_const_reference_type<const T&>
{
    static const bool value = true;
    static const int spec = 2;
    typedef T&       reference_type;
    typedef const T& const_reference_type;
};


struct thing{};

int main()
{
    std::cout << std::boolalpha << is_const_reference_type<thing&>::value << "\n";
}
