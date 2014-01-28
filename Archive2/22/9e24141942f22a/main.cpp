#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

enum A{a=9223372036854775808,b=-1};

int main() {
    
  typedef std::underlying_type<A>::type A_under;   
  int     status;
  char   *realname;

  realname = abi::__cxa_demangle(typeid(A_under).name(), 0, 0, &status);
  std::cout << realname << "\t: " << status << '\n';
  free(realname);
}