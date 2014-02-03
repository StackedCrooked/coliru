#include <type_traits>

class Test
{
public:
  int* p;
};

template< typename, typename = void > struct has_pointer : std::false_type {};
template< typename T > struct has_pointer< T, typename std::enable_if< std::is_pointer< decltype( T::p ) >::value >::type > : std::true_type {};

template< typename T >
void foo( T bla )
{
    static_assert( !has_pointer< T >::value, "T::p is a pointer" );
    // ...
}

int main()
{
    Test test;
    foo( test );
}
