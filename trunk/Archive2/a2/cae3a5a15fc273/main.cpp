#include <iostream>
#include <string>
#include <vector>

template<class C,typename = decltype(std::begin(std::declval<C>()),std::end(std::declval<C>()))>
std::ostream& operator<<(std::ostream& out, const C& v) {
  for(auto x : v) out<<x<<' ';
  return out;
}

int main()
{
    std::string v = "hello";
    std::cout << v << std::endl;
    std::cout << 42 << std::endl;
}
