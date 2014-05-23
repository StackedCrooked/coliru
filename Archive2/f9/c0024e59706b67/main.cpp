#include <iostream>
#include <vector>
#include <deque>

template <template<typename...> class ContainerTT, typename ValueT, typename Filt, typename Tran >
auto filter( ContainerTT<ValueT>& cnt, Filt func, Tran tran ) -> ContainerTT< decltype( tran(cnt[0] ) ) >
{
  ContainerTT<decltype(tran(cnt[9]))> ret;
  for ( auto& item : cnt )
      if ( func( item ) )
          ret.push_back( tran( item ) );
  return ret;
}

int main()
{
  auto is_odd = []( const int x ) { return x % 2 == 1; };
  auto transform = []( int& x ){ return &x; };

  std::vector< int > numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  auto odd_numbers = filter( numbers, is_odd, transform );

  for ( const auto& odd_number : odd_numbers )
    std::cout << *odd_number << '\n';

  std::deque< int > numbers2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  auto odd_numbers2 = filter( numbers2, is_odd, transform );
  for ( const auto& odd_number : odd_numbers2 )
    std::cout << *odd_number << '\n';
}
