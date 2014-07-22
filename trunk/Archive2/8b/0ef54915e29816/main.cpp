#include <iostream>
#include <type_traits>

template<typename T, typename... Interfaces>
typename std::enable_if<sizeof...(Interfaces) == 0, bool>::type
 TryQueryInterfaces()    
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return false;
}

template<typename T, typename... Interfaces>
typename std::enable_if<sizeof...(Interfaces) != 0, bool>::type
 TryQueryInterfaces()    
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return TryQueryInterfaces<T>() || TryQueryInterfaces<Interfaces...>();
}

struct ITrusteeAdmin {};
struct ITrusteeGroupAdmin {};
struct ITrusteeSysAdmin {};

int main()
{
    TryQueryInterfaces<ITrusteeAdmin, ITrusteeGroupAdmin, ITrusteeSysAdmin>();
}
