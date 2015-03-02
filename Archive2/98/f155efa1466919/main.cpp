#include <tuple>
#include <functional>
#include <iostream>

#include <typeinfo>
#include <string>


#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <memory>
 
// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t) 
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << ", " << std::get<N-1>(t);
    }
};
 
template<class Tuple>
struct TuplePrinter<Tuple, 1>{
    static void print(const Tuple& t) 
    {
        std::cout << std::get<0>(t);
    }
};
 
template<class... Args>
void print(const std::tuple<Args...>& t) 
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}
// end helper function

struct Foo_s { int i; std::string k; };

auto make_tuple(Foo_s&& x) -> decltype(std::make_tuple("i",x.i, "k", x.k)) {
    return std::make_tuple("i",x.i, "k", x.k);
}

struct Bar_s { int v; Foo_s w; };




int main(int argc, char *argv[]) {

  auto t1 = std::make_tuple(10, "Test", 3.14);
  
  Foo_s a = {4, "allah"};
  auto t2 = ::make_tuple(std::move(a));
  print(t1);
  print(t2);
  
  return 0;
}