#include <iostream>
#include <memory>

template <typename T, typename TR, typename ... TArgs>
struct has_lambda_operator {
	typedef char yes[1];
	typedef char no[2];
	
	template<typename C, TR (C::*)( TArgs... ) const> struct SFINAE {};

	template <typename C>
	static yes& test(SFINAE<C, &C::operator()>*);

	template <typename>
	static no& test(...);

	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

int main() {
    auto lambda = [] () {};
    typedef decltype(lambda) lambda_t;
    
    std::cout << has_lambda_operator<lambda_t, void>::value << std::endl;
}