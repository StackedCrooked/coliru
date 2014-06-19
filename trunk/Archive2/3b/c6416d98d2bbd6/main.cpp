#include <chrono>
#include <iostream>
#include <memory>

int f( std::shared_ptr< int > ptr )
{
  return ptr.use_count( );
}

int g( std::shared_ptr< int > &ptr )
{
  return ptr.use_count( );
}

int main( int argc, char **argv )
{
  using std::chrono::high_resolution_clock;
  using std::chrono::nanoseconds;
  using std::chrono::duration_cast;

  std::shared_ptr< int > ptr( new int { 42 } );

  high_resolution_clock::time_point start;
  high_resolution_clock::time_point finish;

  int a = 0;
  int b = 0;

  start = high_resolution_clock::now( );
  for ( int i = 0; i < 10000000; ++i )
  {
    a += g( ptr );
  }
  finish = high_resolution_clock::now( );

  std::cout << a << ": " << duration_cast< nanoseconds >( finish - start ).count( ) << std::endl;

  start = high_resolution_clock::now( );
  for ( int i = 0; i < 10000000; ++i )
  {
    b += f( ptr );
  }
  finish = high_resolution_clock::now( );

  std::cout << b << ": " << duration_cast< nanoseconds >( finish - start ).count( ) << std::endl;
  std::cout << std::endl;

  std::cin.get(  );

  return 0;
}