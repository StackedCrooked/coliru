#include <iostream>
#include <tuple>

template<unsigned... Is> struct seq{};

template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};

template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

struct swallow{
    template<class... Ts>
    swallow(Ts&&...){}
};

template<class Os, class Tuple, unsigned I, unsigned... Is>
void print_tuple(Os& os, Tuple const& t, seq<I, Is...>)
{
    os << std::get<I>(t);
    swallow{ (os << ", " << std::get<Is>(t))... };
}

template<class Os, class Tuple>
void print_tuple(Os&, Tuple const&, seq<>){}

template<class Ch, class Traits, class... Args>
std::ostream& operator<<(std::basic_ostream<Ch,Traits>& os,
     std::tuple<Args...> const& t)
{
  os << "(";
  print_tuple(os, t, gen_seq<sizeof...(Args)>());
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