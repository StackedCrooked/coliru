#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

namespace experimental
{
  // C++14's std::make_unique as per N3656 / N3797
  using namespace std;

  template< typename T, typename... Args >
  typename enable_if< !is_array< T >::value, unique_ptr< T > >::type
  make_unique( Args&&... args )
  {
    return unique_ptr< T >( new T( forward< Args >( args )... ) );
  }

  template< typename T >
  typename enable_if< is_array< T >::value && extent< T >::value == 0, unique_ptr< T > >::type
  make_unique( const size_t n )
  {
    using U = typename remove_extent< T >::type;
    return unique_ptr< T >( new U[ n ]() );
  }

  // removing this makes to real difference, in fact the error messages becomes shorter!
  template< typename T, typename... Args >
  typename enable_if< extent< T >::value != 0 >::type
  make_unique( Args&&... args ) = delete;
}

int main()
{
    experimental::make_unique<int[1]>(42);
}
