#include <iostream>
#include <type_traits>

template<typename T>
class test_print_global
{
private:
    int tester[1];
	template <unsigned int>
	struct helper { static const unsigned int value = 1; };

	template<typename R>
	static std::true_type test(int (&a)[helper<sizeof(operator<<(std::cout, std::declval<R>()), 0)>::value]);

	template<typename R>
	static std::false_type test(...);
public:
	static const bool value = std::is_same<decltype(test<T>(tester)), std::true_type>::value;
};

template<typename T>
class test_print_member
{
private:
	int tester[1];
	template <unsigned int>
	struct helper { static const unsigned int value = 1; };

	template<typename R>
	static std::true_type test(int (&a)[helper<sizeof(std::cout.operator<<(std::declval<R>()), 0)>::value]);

	template<typename R>
	static std::false_type test(...);
public:
	static const bool value = std::is_same<decltype(test<T>(tester)), std::true_type>::value;
};

template<typename T>
constexpr bool is_printable() {
    return (test_print_member<T>::value || test_print_global<T>::value) ? true : false;
}

template<typename T, typename = typename std::enable_if<is_printable<T>()>::type>
void print(T t) {
	std::cout << t;
}

template<typename T, typename... Ts, typename = typename std::enable_if<is_printable<T>()>::type>
void print(T t, Ts&&... ts) {
	print(t);
	print(ts...);
}

struct oink{};

int main() {
    print(oink());
	//std::cout << std::boolalpha;
	static_assert(std::is_same<decltype(operator<<(std::cout, "")), decltype(std::operator<<(std::cout, ""))>::value, "ouch!");
	static_assert(std::is_same<decltype(std::cout << ""), decltype(operator<<(std::cout, ""))>::value, "ouch!");
	static_assert(std::is_same<decltype(std::cout << ""), decltype(std::cout.operator<<({""}))>::value, "ouch!");

	std::cout << "std::cout.operator<<(int) \t" << test_print_member<int>::value << '\n';
	std::cout << "std::cout.operator<<(\"\") \t" << test_print_member<decltype("")>::value << '\n';
	std::cout << "std::cout.operator<<(oink) \t" << test_print_member<oink>::value << '\n';

	std::cout << "operator<<(std::cout, int) \t" << test_print_global<int>::value << '\n';
	std::cout << "operator<<(std::cout, \"\") \t" << test_print_global<decltype("")>::value << '\n';
	std::cout << "operator<<(std::cout, oink) \t" << test_print_global<oink>::value << '\n';

	std::cout << "is_printable<int>() \t" << is_printable<int>() << '\n';
	std::cout << "is_printable<decltype(\"\")> \t" << is_printable<decltype("")>() << '\n';
	std::cout << "is_printable<oink>() \t" << is_printable<oink>() << '\n';
}