
#include <type_traits>
#include <utility>
#include <iomanip>
#include <iostream>

namespace {

template<class U, class T>
static auto
has_member_f_impl(signed)
    -> decltype(
        std::declval<T&>().f(std::declval<U&>()),
    	std::true_type{}
	)
;

template<class, class>
static std::false_type
has_member_f_impl(...);

template<class U, class T>
static auto
has_non_member_f_impl(signed)
    -> decltype(
        f(std::declval<U&>(), std::declval<T&>()),
		std::true_type{}
	)
;

template<class, class>
static std::false_type
has_non_member_f_impl(...);

} // anonymous namespace

template<class U, class T>
struct has_member_f
	: public decltype(has_member_f_impl<U, T>(0))
{};

template<class U, class T>
struct has_non_member_f
	: public decltype(has_non_member_f_impl<U, T>(0))
{};


// test
struct B {
    template<class T>
    void f(T&) {}
};

struct D : public B {};

template<class U, class T>
void f(U&, T&) {}

signed main() {
    std::cout
        << std::boolalpha
        << has_member_f<int, D>::value << '\n'
        << has_non_member_f<int, D>::value << '\n'
    ;
    return 0;
}
