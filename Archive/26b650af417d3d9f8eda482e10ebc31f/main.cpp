#include <iostream>
#include <tuple>


//
// PRETTY PRINT TUPLE
//
template<std::size_t> struct int_{}; // compile-time counter

template<class Ch, class Tr, class Tuple, std::size_t I>
void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, int_<I>) {
  print_tuple(os, t, int_<I-1>());
  os << ", " << std::get<I>(t);
}

template<class Ch, class Tr, class Tuple>
void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, int_<0>){
  os << std::get<0>(t);
}

template<class Ch, class Traits, class... Args>
std::ostream& operator<<(std::basic_ostream<Ch,Traits>& os,
     std::tuple<Args...> const& t)
{
  os << "(";
  print_tuple(os, t, int_<sizeof...(Args)-1>());
  return os << ")";
}



//
// TEST
//
namespace test {
    
    
using std::tie;
    
    
struct Point
{
    int x, y;
};

auto tie(Point & point) -> decltype(tie(point.x, point.y))
{
    return tie(point.x, point.y);
}


struct Person
{
    const std::string name;
    int age;
};
    
    
auto tie(Person & person) -> decltype(tie(person.name, person.age))
{
    return tie(person.name, person.age);
}
    
} // namespace test


int main()
{
    test::Point point = { 3, 4 };
    std::cout << tie(point) << std::endl;
    
    test::Person person{"John", 60};
    std::cout << tie(person) << std::endl;
}