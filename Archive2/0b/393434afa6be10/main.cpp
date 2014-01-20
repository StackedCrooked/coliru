#include <cstddef>
#include <iostream>
#include <typeinfo>

template <typename... Args>
using index_sequence_for = std::integral_constant<size_t, sizeof...(Args)>;

template <typename... Args>
class X {
public:
	static void print()
	{
        typedef index_sequence_for<Args...> indices_type;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "sizeof...(Args)                     = " << sizeof...(Args) << std::endl;
        std::cout << "index_sequence_for<>::size()        = " << index_sequence_for<>::value << std::endl;
        std::cout << "index_sequence_for<Args...>::size() = " << index_sequence_for<Args...>::value << std::endl;
        std::cout << "indices_type::size()                = " << indices_type::value << std::endl;
        std::cout << "---\n";
        std::cout << std::boolalpha << (typeid(index_sequence_for<>) == typeid(index_sequence_for<Args...>)) << std::endl;
        std::cout << std::boolalpha << (typeid(index_sequence_for<>) == typeid(indices_type)) << std::endl;
	}
};

int main()
{
    X<>::print();
}