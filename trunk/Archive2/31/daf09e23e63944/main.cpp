#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, std::ostream&>::type
operator<<(std::ostream& os, const T& vec)
{
    os << vec + 42 << "\n";
    return os;
}

int main()
{
    std::cout << 42 << std::endl;
}
