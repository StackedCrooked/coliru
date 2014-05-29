
#include <iostream>
#include <type_traits>

template<class First, class Second, class...Rest>
bool all_equal(const First& first, const Second& second, const Rest&...rest) 
{
    using item_type = typename std::common_type<First const*,Second const*,Rest const*...>::type;
    item_type items[] {&first, &second, &rest...};
    for(auto const & item : items) if ( *item != *(items[0]) ) return false;
    return true;
}


int main() {
    std::cout << all_equal(4, 4, 4);    
}