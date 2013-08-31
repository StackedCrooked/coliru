#include <boost/type_traits.hpp>

template <typename T, class C>
struct is_member_function_pointer_of
    : public boost::false_type
{};

template <typename FT, class C>
struct is_member_function_pointer_of<FT C::*, C>
    : public boost::is_function<FT>::type
{};

struct a { void func(){} };
struct b {};

template<class fnc, class c>
bool test(fnc f, c* pC) {
    return is_member_function_pointer_of<fnc, c>::value;
}

#include <iostream>

int main() {
    bool b1 = test(&a::func, new a);
    bool b2 = test(&a::func, new b);
    std::cout << std::boolalpha << b1 << "\n" << b2 << std::endl;
}
