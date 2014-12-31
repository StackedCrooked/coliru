#include <type_traits>

template <template <typename...> class Needle, template <typename...> class... Haystack>
struct is_one_of;

template <template <typename...> class Needle, template <typename...> class Head, template <typename...> class... Tail>
struct is_one_of<Needle, Head, Tail...> : is_one_of<Needle, Tail...>::type {};

template <template <typename...> class Needle, template <typename...> class... Tail>
struct is_one_of<Needle, Needle, Tail...> : std::true_type {};

template <template <typename...> class Needle>
struct is_one_of<Needle> : std::false_type {};


#include <vector>
#include <set>
#include <list>
#include <map>
int main()
{
    // This won't fail: vector is on the list
    static_assert(is_one_of<std::vector, std::map, std::list, std::vector, std::set>{}, "!");
    
    // This will fail: vector in not in the haystack
    static_assert(is_one_of<std::vector, std::map, std::list, std::set>{}, "!");
}
