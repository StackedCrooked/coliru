#include<iostream>
#include<utility>

namespace asdf {
    template <typename T>
	std::enable_if_t<std::is_class<T>{}, T> declval();
}

template <class T>
struct A
{
	using type = int;
	using foo = typename decltype(asdf::declval<A>())::type;
};

namespace std
{
	template <>
	class is_class<A<void>> : public std::false_type {};
}

int main() {
	A<void> a;
}
