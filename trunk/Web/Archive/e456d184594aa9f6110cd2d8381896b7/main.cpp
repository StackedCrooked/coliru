#include <type_traits>
#include <iterator>
#include <utility>
#include <iosfwd>

template<class T> using Invoke = typename T::type;
template<class C, class T = void>
using EnableIf = typename std::enable_if<C::value, T>::type;
template<class T>
using Strip = Invoke<std::remove_cv<Invoke<std::remove_reference<T>>>>;

namespace aux{
using std::begin;
using std::end;
template<class C> auto adl_begin(C&& c) -> decltype(begin(std::forward<C>(c)));
template<class C> auto adl_end(C&& c) -> decltype(end(std::forward<C>(c))); 
}

using X = int;

// general container
template<class Ch, class Traits, class Cont>
auto operator<<(std::basic_ostream<Ch, Traits>& os, Cont const& c)
  -> decltype(void(aux::adl_begin(c)), void(aux::adl_end(c)),
       void(EnableIf<std::is_same<Strip<decltype(*aux::adl_begin(c))>, X>, int>()), os)
{
  using std::begin;
  using std::end;
  // use unqualified calls to `begin` and `end` to get iterators
  // or use a range-based for-loop
  for(auto&& e : c)
    /*your special logic*/
    os << e << os.widen(' ');
    
  return os << os.widen('\n');
}

// mapping container
template<class Ch, class Traits, class Cont>
auto operator<<(std::basic_ostream<Ch, Traits>& os, Cont const& c)
  -> decltype(void(aux::adl_begin(c)), void(aux::adl_end(c)),
       void(EnableIf<std::is_same<Strip<decltype(aux::adl_begin(c)->second)>, X>, int>()), os)
{
  using std::begin;
  using std::end;
  // use unqualified calls to `begin` and `end` to get iterators
  // or use a range-based for-loop
  for(auto&& e : c)
    /*your special logic*/
    os << e.second << os.widen(' ');
    
  return os << os.widen('\n');
}

#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <iostream>

int main(){
  std::vector<X> v{1,2,3};
  std::list<X> l{1,2,3};
  std::deque<X> d{1,2,3};
  std::set<X> s{1,2,3};
  std::map<int, X> m{{1,1},{2,2},{3,3}};
  
  std::cout << v << l << d << s << m;
}