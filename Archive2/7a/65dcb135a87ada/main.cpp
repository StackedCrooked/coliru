#include <iostream>

void foo( int ) {std::cout << "Foo\n";}
void bar( int * ) {std::cout << "Bar\n";}

int main()
{
    foo( int() );  // works. a temporary int - value initialized.
    
    bar( {} );    // how to create a temporary int *?
    bar( (int*){} );    // how to create a temporary int *?
    using p = int*;
    bar( p() );    // how to create a temporary int *?
}