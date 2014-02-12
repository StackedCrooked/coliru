#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
#include <vector>
#include <list>
#include <tuple>


template<typename... Containers>
std::tuple<typename Containers::value_type...>
foo( const Containers &...args ) {
    return {};
}

int main()
{
    foo( std::list<int>( ), std::vector<float>( ) );

    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
