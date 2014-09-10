#include <iostream>
#include <map>

    struct A { };
    struct C { C(C&&)=delete; };
    struct B { B() = delete; B(B&&)=delete; B(C&&, C&&) {}; };
    
int main() {
    std::map< int, std::pair<A,B> > test;
    // test.emplace( 0, std::make_pair( A{}, B{} ); // does not compile
    // test.emplace( 0, std::make_pair( A{}, B{C{},C{}} ); // does not compile
    test.emplace( std::piecewise_construct,
      std::make_tuple(0),
      std::forward_as_tuple(
        std::piecewise_construct,
        std::forward_as_tuple(A{}),
        std::forward_as_tuple( C{}, C{} )
      )
    ); // compiles!
}
