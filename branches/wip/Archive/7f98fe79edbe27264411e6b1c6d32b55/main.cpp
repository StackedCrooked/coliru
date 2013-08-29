#include <iterator>
#include <utility>

namespace aux {
  using std::begin;
  using std::end;
  template<class T>
  auto adl_begin(T&& v) -> decltype(begin(std::forward<T>(v))); // no implementation
  template<class T>
  auto adl_end(T&& v) -> decltype(end(std::forward<T>(v))); // no implementation
}

template<class C, class T = void>
using EnableIf = typename std::enable_if<C::value, T>::type;

template<typename T, typename Iterator, typename=void>
struct is_iterator_of_type: std::false_type {};

template<typename T, typename Iterator>
struct is_iterator_of_type<
  T,
  Iterator,
  typename std::enable_if<
    std::is_same<
      T,
      typename std::iterator_traits< Iterator >::value_type
    >::value
  >::type
>: std::true_type {};

#include <ostream>

template<class Ch, class Tr, class Container>
auto operator<<( std::basic_ostream<Ch,Tr>& stream, Container const& c ) ->
  EnableIf<is_iterator_of_type<double, decltype(void(aux::adl_begin(c)), aux::adl_end(c))>, std::basic_ostream<Ch,Tr>&>
{
  using std::begin; using std::end;
  for(auto& e : c){
    stream << e << " ";
  }
  return stream;
}

#include <vector>
#include <iostream>

int main(){
    std::vector<double> v{3.14, 13.37, 17.29};
    double a[] = {1.0, 2.0, 3.0};
    std::cout << v << "\n";
    std::cout << a << "\n";
}