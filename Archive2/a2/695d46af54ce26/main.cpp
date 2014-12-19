#include <utility>

template< typename... Ts >
void foo( Ts&&... );

template< typename... Ts >
void bar( Ts&&... ts )
{
    foo( std::forward<Ts...>(ts)... );
}

int main()
{
    bar();
    bar( true );
    bar( true, 0 ); // doesn't compile
}
