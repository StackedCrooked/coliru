#include <type_traits>
#include <boost/variant.hpp>

template <std::size_t, typename, typename...> struct find_;

template <std::size_t pos, typename T, typename Other, typename... Args>
struct find_<pos, T, Other, Args...> : find_<pos+1, T, Args...> {};
template <std::size_t pos, typename T, typename... Args>
struct find_<pos, T, T, Args...> : std::integral_constant<std::size_t, pos> {};
template <std::size_t pos, typename T>
struct find_<pos, T> : std::integral_constant<std::size_t, std::size_t(-1)> {};

template <typename T, typename... Args>
using find = find_<0, T, Args...>;

template <typename, typename> struct IndexInVariant;

template <typename T, typename... Types>
struct IndexInVariant<boost::variant<Types...>, T> :
    find<typename std::remove_cv<T>::type, Types...> {};
        
int main()
{
    static_assert( IndexInVariant< boost::variant<int, float, std::string>, std::string >::value == 2, "" );
    static_assert( IndexInVariant< boost::variant<int, float, std::string>, char >::value == -1, "" );
}