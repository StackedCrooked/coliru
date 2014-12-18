#include <iostream>
#include <vector>

template<class I>
class _reversed
{
  const I * citerable;
  I * iterable;
public:
  _reversed( const I & iterable ) : citerable( &iterable ), iterable( nullptr ) {}
  _reversed( I & iterable ) : iterable( &iterable ), citerable( nullptr ) {}
  typename I::const_reverse_iterator begin() const { return citerable->crbegin(); }
  typename I::const_reverse_iterator end() const { return citerable->crend(); }
  typename I::reverse_iterator begin() { return iterable->rbegin(); }
  typename I::reverse_iterator end() { return iterable->rend(); }
};

static const class _just_reversed {} just_reversed;
template<class I>
_reversed<I> operator | ( I & t,  _just_reversed )
{
  return _reversed<I>( t );
}
template<class I>
const _reversed<I> operator | ( const I & t,  _just_reversed )
{
  return _reversed<I>( t );
}

int main()
{
  std::vector<int> omg;
  omg.emplace_back( 3 );
  omg.emplace_back( 4 );
  omg.emplace_back( 5 );

  const std::vector<int> omgc( omg );
  // const
  for ( auto && e : omgc | just_reversed )
  {
    std::cout << e << std::endl;
    // e = 42;
  }
  // non-const
  for ( auto && e : omg | just_reversed )
  {
    e = 42;
    std::cout << e << std::endl;
  }

  return 0;
}