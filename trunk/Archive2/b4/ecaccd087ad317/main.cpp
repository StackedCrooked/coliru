#include <iostream>
#include <vector>
#include <map>

typedef unsigned long int u64;
typedef std::vector< u64 > Matrix;
typedef std::map< u64, Matrix > Cache;

const u64 q[] = { 0, 1, 1, 1 };
const Matrix Q( q, q + 4 );

Matrix mul( const Matrix& a, const Matrix& b, const u64 m )
{
  Matrix c( 4 );

  for ( size_t i = 0; i < 2; ++i )
    for ( size_t j = 0; j < 2; ++j )
      for ( size_t k = 0; k < 2; ++k )
        c[ i * 2 + j ] += ( a[ i * 2 + k ] * b[ k * 2 + j ] ) % m;

  return c;
}

Matrix power( const Matrix& a, const u64 p, const u64 m )
{
  static Cache cache;
  Cache::const_iterator iter;
  Matrix k( 4 );
  Matrix r( 4 );

  if ( p == 1 )
    return a;

  iter = cache.find( p );
  if ( iter != cache.end() )
    return iter->second;

  k = power( a, p / 2, m );
  r = mul( k, k, m );
  cache[ p ] = r;

  return r;
}

void get_powers( std::vector< u64 >& powers, const u64 n )
{
  for ( size_t i = 0; i < 64; ++i )
    if ( ( n >> i ) & 1UL )
      powers.push_back( n & ( 1UL << i ) );
}

void get_matrices( std::vector< Matrix >& matrices, const std::vector< u64 >& powers, const u64 m )
{
  for ( size_t i = 0; i < powers.size(); ++i )
    matrices.push_back( power( Q, powers[ i ], m ) );
}

u64 fib3( const u64 n, const u64 m )
{
  if ( n < 2 )
    return n;

  std::vector< u64 > powers;
  get_powers( powers, n );

  std::vector< Matrix > matrices;
  get_matrices( matrices, powers, m );

  Matrix m1( 4 ), m2( 4 ), r( 4 );

  while ( matrices.size() > 1 )
  {
    m1 = matrices.back();
    matrices.pop_back();
    m2 = matrices.back();
    matrices.pop_back();
    r = mul( m1, m2, m );
    matrices.push_back( r );
  }

  return matrices[ 0 ][ 2 ];
}

int main()
{
  u64 n = 0;
  u64 m = 0;
  std::cin  >> n >> m;
  std::cout << fib3( n, m );

  return 0;
}