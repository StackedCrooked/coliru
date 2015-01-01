#include <iostream>
#include <vector>
#include <deque>
#include <type_traits>

namespace detail
{
    template<class>
    struct sfinae_true : std::true_type{};

    template<class T, class A0>
	static auto test_reserve(int)
		->sfinae_true<decltype(std::declval<T>().reserve(std::declval<A0>()))>;
	template<class, class A0>
	static auto test_reserve(long)->std::false_type;

	template<class T, class A0>
	static auto test_resize(int)
		->sfinae_true<decltype(std::declval<T>().resize(std::declval<A0>()))>;
	template<class, class A0>
	static auto test_resize(long)->std::false_type;
}

//check if class T have reserve(Arg) function
template<class T, class Arg>
struct HasReserve : decltype(detail::test_reserve<T, Arg>(0)){};


//check if class T have resize(Arg) function
template<class T, class Arg>
struct HasResize : decltype(detail::test_resize<T, Arg>(0)){};

//enable if resize function exists and there is no reserve function
template<class T1, class T2>
typename std::enable_if<HasResize< T1, typename T1::size_type>::value &&
	(!HasReserve< T1, typename T1::value_type>::value), void>::type
	inline reserveOrResize(T1& dst, T2&& src, typename T2::size_type newSize){
		static_assert(std::is_lvalue_reference<T1&>::value, "You must pass lvalue_refrence as first parameter");
		static_assert(std::is_rvalue_reference<T2&&>::value, "You must pass rvalue_refrence as second parameter");
		int loc = dst.size() + 1;
		dst.resize(newSize);
		std::cout << "Resizing\n";
		for (auto&& elem : src){
			dst[loc++] = std::move(elem);
		}
}

//enable if  reserve function exists
template<class T1, class T2>
typename std::enable_if<HasReserve< T1, typename T1::size_type>::value, void>::type
inline reserveOrResize(T1& dst, T2&& src, typename T2::size_type newSize){
	static_assert(std::is_lvalue_reference<T1&>::value, "You must pass lvalue_refrence as first parameter");
	static_assert(std::is_rvalue_reference<T2&&>::value, "You must pass rvalue_refrence as second parameter");
	src.reserve(newSize);
	std::cout << "Reserving\n";
	for (auto&& elem : src){
		dst.push_back(std::move(elem));
	}
}

//push_back container T2 at the end of Container T1
//T2 must be rvalue refrence
template<class T1, class T2>
void push_back(T1& dst, T2&& src){
	static_assert(std::is_lvalue_reference<T1&>::value, "You must pass lvalue_refrence as first parameter");
	static_assert(std::is_rvalue_reference<T2&&>::value, "You must pass rvalue_refrence as second parameter");
	reserveOrResize(dst, std::move(src), src.size());
}

int main(){
	std::vector<int> vec;
	push_back(vec, std::vector<int>(10));
}
