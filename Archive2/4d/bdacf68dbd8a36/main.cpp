#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T, typename... Args>
struct is_nothrow_constructible_helper
    : public integral_constant<bool, noexcept(T(declval<Args>()...))> {};
    
class A
{
public:
    A(int) {}
    A(short) noexcept {}
};

int main()
{    
    static_assert(is_nothrow_constructible_helper<A, int>::value  == false, "");
    static_assert(is_nothrow_constructible_helper<A, short>::value == true, "");
}
