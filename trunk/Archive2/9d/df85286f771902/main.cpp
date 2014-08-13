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
    struct placeholder {};

    template< typename... Ts >
    struct CheckVaradicArgs
    {
        typedef 
            typename std::enable_if< 
                all_true< std::is_convertible<Ts, T>... >::value
                , placeholder >::type type;
    };

    template< typename... Ts >
    myobject( placeholder check, Ts... params )
    {}    
public:

    myobject( const myobject& other )
    {
        std::cout << "Copy constructor" << std::endl;
    }

    myobject( const char * other )
    {
        std::cout << "const char * constructor" << std::endl;
    }
    
    template< typename... Ts >
    myobject( Ts... params )
    : myobject( typename CheckVaradicArgs<Ts...>::type(), params... )
    {
        std::cout << "Ts constructor with " << sizeof...(params) << std::endl;
    }

};

int main() {
    myobject<int> something;
    myobject<int> something2(0);
    char * p = nullptr;
    myobject<int> something3(p);
    myobject<int> somethingelse(something);
}