#include <type_traits>
#include <algorithm>

struct F
{
    int operator()(bool a) { return 1; }
};

namespace details {
  namespace adl_aux {
    // a namespace where we can do argument dependent lookup on begin and end
    using std::begin; using std::end;
    // no implementation, just used to help with ADL based decltypes:
    template<class R>
    decltype( begin( std::declval<R>() ) ) adl_begin(R&&);
    template<class R>
    decltype( end( std::declval<R>() ) ) adl_end(R&&);
  }
  // pull them into the details namespace:
  using adl_aux::adl_begin;
  using adl_aux::adl_end;
}
// two aliases.  The first takes a Range or Container, and gives
// you the iterator type:
template<class Range>
using iterator = decltype( details::adl_begin( std::declval<Range&>() ) );
// the second is syntactic sugar on top of `std::iterator_traits`:
template<class Iterator>
using value_type = typename std::iterator_traits<Iterator>::value_type;

template<class T>
using decayed_lvalue = typename std::decay<T>::type&; 

template<
  typename Range,
  typename Selector,
  typename T=value_type<iterator<Range&>>,
  typename R=typename std::result_of<decayed_lvalue<Selector>(T)>::type
>
std::vector<R> select(Range&& in, Selector&& s) {
  std::vector<R> v;
  using std::begin; using std::end;
  std::transform(begin(in), end(in), back_inserter(v), std::forward<Selector>(s));
  return v;
}

int main()
{    
    std::vector<bool> a;    
    F f;
    const F& r = f;    
    select(a, r);        
}
