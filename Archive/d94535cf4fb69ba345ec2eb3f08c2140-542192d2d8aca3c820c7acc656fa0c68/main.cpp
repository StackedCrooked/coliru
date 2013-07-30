#include <type_traits>

template <typename T, typename U>
auto has_plus(T const& t, U const& u) -> decltype(std::declval<T>() + std::declval<U>(), std::true_type());
std::false_type has_plus(...);

template <typename T> using Addition = decltype(has_plus(std::declval<T>(), std::declval<T>()));

#include <iostream>

int main()
{
    std::cout << std::boolalpha << Addition<int>::value         << "\n";
	std::cout << std::boolalpha << Addition<void*>::value       << "\n";
	std::cout << std::boolalpha << Addition<std::string>::value << "\n";
}
