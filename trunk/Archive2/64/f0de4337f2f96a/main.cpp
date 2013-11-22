#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cxxabi.h>

std::string demangle(const char* mangledName);

template<typename T>
struct A{
  void f();
 
  template< typename U>
  void g (const U &u);
  
  template< typename U>
  void g2 (const U &u);
};

template<typename T>
void A<T>::f() {
    std::cout << demangle( typeid( A<T> ).name() ) << "::f();"<< std::endl;
}

template<typename T>
template<typename U>
void A<T>::g( const U& u ) {
    std::cout << "g ( const "<< demangle( typeid(U).name() ) << "& )" << std::endl;
}

int main()
{
    A<int> a;
    a.f();
    a.g( 1u );
    a.g( a );
    a.g( std::string{} );
}

std::string demangle(const char* mangledName) {
    int status;
    char* result = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
    switch(status) {
    case -1:
        std::cerr << "Out of memory!" << std::endl;
        exit(1);
    case -2:
        return mangledName;
    case -3: // Should never happen, but just in case?
        return mangledName;
    }
    std::string name = result;
    free(result);
    return name;
}