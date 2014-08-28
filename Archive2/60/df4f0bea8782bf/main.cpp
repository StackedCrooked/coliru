#include <type_traits>
#include <istream>

template<class> struct deserialising{};

namespace detail
{
template<class> struct dependent_false : std::false_type{};

template<class T>
void deserialise(deserialising<T>, std::istream&){ static_assert(dependent_false<T>{}, "no overload for type"); }
} // detail::

template<class T>
T deserialise(std::istream& in)
{
    using detail::deserialise;
    return deserialise(deserialising<T>{}, in);
}

#include <sstream>
#include <iostream>

int deserialise(deserialising<int>, std::istream& in)
{
    // not good code
    int i = 0;
    in >> i;
    return i;
}

int main()
{
    std::stringstream test("123");
    auto i = deserialise<int>(test);
    std::cout << i;
}