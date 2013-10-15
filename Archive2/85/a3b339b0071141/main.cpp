#include <iostream>
#include <type_traits>
#include <tuple>
#include <functional>

template< class ... Args >
struct mytuple : public std::tuple<Args...>
{
    using std::tuple<Args...>::tuple;

    template< typename T >
    auto& operator []( T t ) noexcept
    {
        return std::get< std::is_placeholder<T>::value - 1 >(*this);
    }

    template< typename T >
    auto const& operator []( T t ) const noexcept
    {
        return std::get< std::is_placeholder<T>::value - 1 >(*this);
    }
};

int main()
{
    using person = mytuple< std::string, int, double, char>;

    using namespace std::placeholders;

    person s = std::make_tuple("Bjarne Stroustrup", 63, 3.14, '7' );
    auto name = s[ _1 ];
    auto old  = s[ _2 ];
    auto number = s[ _3 ];
    auto symbol = s[ _4 ];

    std::cout << "name: "   << name << '\t'
              << "old: "    << old << '\t'
              << "number: "  << number<< '\t'
              << "symbol: " << symbol<< '\t'
              << std::endl;
}