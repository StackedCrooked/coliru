#include <iostream>
#include <numeric>
#include <functional>
#include <algorithm>

template <typename T>
struct is_floating_point
{
    static const bool value;
};

template <typename T>
const bool is_floating_point<T>::value =!std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_bounded;

template<typename T>
class Foo{
public:
	template<typename = typename std::enable_if<
		std::is_integral<T>::value&& !std::is_floating_point<T>::value>::type>
	Foo(T value1 = 50, T value2 = -50) :value1_(value1), value2_(value2){}

	template<typename = typename std::enable_if<
		std::is_floating_point<T>::value>::type>
	Foo(T value1 = 0.5, T value2 = -0.5,void* dummy=0) : value1_(value1), value2_(value2){}
	T value1_, value2_;
};

int main()
{
	Foo<float> test;
	std::cout << test.value1_ << " " << test.value2_ << '\n';

	Foo<int> test2;
	std::cout << test2.value1_ << " " << test2.value2_;
}