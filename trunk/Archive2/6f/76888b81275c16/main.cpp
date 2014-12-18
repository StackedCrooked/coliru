#include <iostream>
#include <vector>
#include <iterator>

template<class I>
class _reversed
{
  I & iterable;
public:
  _reversed( I & iterable ) : iterable( iterable ) {}
  auto begin() -> decltype(iterable.rbegin())
  { return iterable.rbegin(); }

  auto end() -> decltype(iterable.rend())
  { return iterable.rend(); }
};

static struct _just_reversed {} just_reversed;

template<class I>
_reversed<I> operator | ( I & t,  _just_reversed )
{
  return _reversed<I>( t );
}


int main()
{
  std::vector<int> omg;
  omg.emplace_back( 3 );
  omg.emplace_back( 4 );
  omg.emplace_back( 5 );

//  std::vector<int> omg = {3, 4, 5};
  //int omg[] = {3, 4, 5}; // Упс

//  const std::vector<int> omgc( omg );
  const std::vector<int> omgc( std::begin(omg), std::end(omg) );

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