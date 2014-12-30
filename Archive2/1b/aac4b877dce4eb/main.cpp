#include <iostream>
#include <tuple>

template< typename ... aux, typename ... arg >
void fn( arg ... a ) {
    std::tuple< aux ... > more {}; // The tuple elements are value-initialized.
    
    std::cout << sizeof ... (aux) << " defaulted and " << sizeof ... (arg) << " explicit\n";
}
    
int main() {
    fn< int >( 3 );
}
