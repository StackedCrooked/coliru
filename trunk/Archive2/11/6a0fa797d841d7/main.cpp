#include <type_traits>
#include <iostream>

template< typename... CONDITIONS >
struct all_true;

template<>
struct all_true<>
{
    const static bool value = true;
};

template< typename CONDITION, typename... CONDITIONS >
struct all_true< CONDITION, CONDITIONS... >
{
    const static bool value = CONDITION::value && all_true<CONDITIONS...>::value;
};

template< class T >
class myobject
{

    template< typename... Ts >
    using CheckVaradicArgs =
            typename std::enable_if< 
                all_true< std::is_convertible<Ts, T>... >::value
                >::type;
public:

    myobject( const myobject& other )
    {
        std::cout << "Copy constructor" << std::endl;
    }

    template< typename... Ts, CheckVaradicArgs<Ts...>* = nullptr >
    myobject( Ts... params )
    {
        std::cout << "Ts constructor with " << sizeof...(params) << std::endl;
    }

};

int main() {
    myobject<int> something;
    myobject<int> something2(0);
    myobject<int> something3("oops");
    myobject<int> somethingelse(something);
}