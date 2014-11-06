#include <iostream>
#include <type_traits>
#include <vector>

template <typename T> struct IsCallableWithBeginAndEndImpl
{
    struct no_type { char a[1]; };
    struct yes_type { char a[2]; };
    
	template < typename T1>
	static no_type is(...);

	template < typename T1>
	static decltype(std::begin(std::declval<T1>()), std::end(std::declval<T1>()), yes_type{}) is(int);
	
	static const bool value = sizeof(is<T>(0)) == sizeof(yes_type);
};

template<typename T>    
struct IsCallableWithBeginAndEnd : public std::integral_constant<bool, IsCallableWithBeginAndEndImpl<T>::value> {};

int main() {
    static_assert(IsCallableWithBeginAndEnd<std::vector<int>>::value == true, "vector has iterators");
    static_assert(IsCallableWithBeginAndEnd<int>::value == false, "int can't return an iterator");
    std::cout << "done!" << std::endl;
}
