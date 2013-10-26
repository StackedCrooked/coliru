#include <iostream>
#include <string>
#include <vector>

namespace helper
{
    using namespace std;
    template<typename C,typename=decltype(begin(std::declval<C>()),end(std::declval<C>()))>
    struct supports_begin_end
    {
        using type = void;
    };
    
    template<>
    struct supports_begin_end<std::string>;
}

template<class C,typename = typename helper::supports_begin_end<C>::type>
std::ostream& operator<<(std::ostream& out, const C& v) {
  for(auto x : v) out<<x<<' ';
  return out;
}

int main()
{
    std::vector<int> v { 1, 2, 3, 4 };
    std::cout << v << std::endl;
    std::cout << 42 << std::endl;
    std::cout << std::string( "Hello, world" ) << std::endl;
}
