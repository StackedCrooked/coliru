#include <type_traits>
template< typename T >
using cond = std::conditional_t< true , std::true_type , std::false_type >::value;

template< typename T , typename = std::enable_if_t< cond< T > , T > >
void func( T t ) {}

int main() {
    func( 1 );
}