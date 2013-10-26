#include <iostream>
#include <string>
#include <vector>

namespace supports_begin_end
{
    using namespace std;

    template<typename C,typename=int>
    struct impl2
    {
    };

    template<typename C>
    struct impl2< C, decltype(std::declval<C>().begin(),std::declval<C>().end(),0) >
    {
        using type = void;
    };

    template<typename C,typename=decltype(begin(std::declval<C>()),end(std::declval<C>()))>
    struct impl : impl2<C>
    {
        using type = void;
    };
    
    template<>
    struct impl<std::string>;
}

template<class C,typename = typename supports_begin_end::impl<C>::type>
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
