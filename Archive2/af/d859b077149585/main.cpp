#include <iostream>
#include <type_traits>
#include <tuple>
#include <vector>

template<typename T>
using is_regular = std::integral_constant<bool,
    	std::is_default_constructible<T>::value &&
		std::is_copy_constructible<T>::value &&
		std::is_move_constructible<T>::value &&
		std::is_copy_assignable<T>::value &&
		std::is_move_assignable<T>::value>;

template<typename T>
std::false_type check_equality_comparable(const T&, ...);

template<typename T>
auto check_equality_comparable(const T& t, int)
	-> typename std::is_convertible<decltype(t==t), bool>::type;

template<typename T>
using is_equality_comparable = decltype(check_equality_comparable(std::declval<const T&>(), 1));

template<typename T>
void test_regular()
{
	static_assert(std::is_default_constructible<T>::value, "no default ctor");
	static_assert(std::is_copy_constructible<T>::value, "no copy ctor");
	static_assert(std::is_move_constructible<T>::value, "no move ctor");
	static_assert(std::is_copy_assignable<T>::value, "no copy assignment");
	static_assert(std::is_move_assignable<T>::value, "no move assignment");
	static_assert(is_equality_comparable<T>::value, "not equality comparable");
}

struct my 
{
	std::vector<int> v;
	my() = default;
	my(const my&) = default;
	friend bool operator==(const my&, const my&);
	//my(my&&) = default;
};

template<typename T>
struct lexical_cast_fn
{
    template<typename U>
	T operator()(const U& u) const { return static_cast<T>(u); }
};

//template<typename T>
//constexpr lexical_cast_fn lexical_cast{}; // variable template

template<class T>
decltype(auto) my_move(T&& t) 
{ 
    using RT = std::remove_reference_t<T>;
    static_assert(!std::is_const<RT>::value, "cant move const");
    return static_cast<RT>(t);
}

//
template<std::size_t I, class...Args>
auto n_th_type() noexcept(noexcept(std::declval<typename std::tuple_element<I, std::tuple<Args...>>::type>()))
-> typename std::tuple_element<I, std::tuple<Args...>>::type;
//

int main() 
{
    my m{};
    auto m1 = my_move(m);
    auto m2 = my_move(my{});
    const my mc{};
    //auto m3 = my_move(mc);
	test_regular<my>();
	//lexical_cast<int>(4);
    std::cout << "done";
	return 0;
}
