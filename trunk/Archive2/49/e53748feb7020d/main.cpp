#include <type_traits>

class Test
{
public:
  int* p;
};

template< typename T >
typename std::enable_if< std::is_pointer< decltype( T::p ) >::value >::type
foo( T bla ) { static_assert( sizeof( T ) == 0, "T::p is a pointer" ); }

template< typename T >
void foo( T bla )
{
}

int main()
{
    Test test;
    foo( test );
}
