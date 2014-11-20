#include <type_traits>
#include <boost/variant.hpp>

template <std::size_t pos, typename T, typename Tail, typename... Args>
struct find_ : find_<pos+1, T, Args...> {};
template <std::size_t pos, typename T, typename... Args>
struct find_<pos, T, T, Args...> : std::integral_constant<std::size_t, pos> {};
template <typename T, typename... Args>
using find = find_<0, T, Args...>;

template <typename, typename> struct IndexInVariant;

template <typename T, typename... Types>
struct IndexInVariant<boost::variant<Types...>, T> :
    find<T, Types...> {};
        
int main()
{
    static_assert( IndexInVariant< boost::variant<int, float, std::string>, std::string >::value == 2, "" );
}