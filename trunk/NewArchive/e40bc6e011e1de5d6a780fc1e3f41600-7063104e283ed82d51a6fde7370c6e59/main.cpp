#include <type_traits>
#include <utility>
#include <cassert>
#include <iostream>
#include <memory>

template <typename T>
void RValuesOnly ( T&& thisisanrvalue ) {
    
}

int main () {
 
    std::unique_ptr<int> sexylvalue (new int(24));
    RValuesOnly ( sexylvalue ); // should fail
    RValuesOnly ( std::move( sexylvalue ) ); // should work
    
}