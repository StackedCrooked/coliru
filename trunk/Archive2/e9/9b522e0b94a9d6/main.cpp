///////////////////////////////////////////////////////////////////////////////////////////
////                                        Лист 2
///////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <ios>
#include <math.h>

// возведение в квадрат
inline double sqr( const double a )
{
  return a*a;
}

/////////////////////////////////////////////////////////////////////////////////////////
//                                        Задание 4
/////////////////////////////////////////////////////////////////////////////////////////

// заполнить файл значениями
void fill_file( const std::string & file_name )
{
  std::ofstream raw_data( file_name, std::ios::binary );

  const double data [] =
  {
    10.1, 11.3, 45.5, 41.3, 425.6 ,12.6, 21.5 // x
    ,30.4, 1.5, 5.71, 1.3, 5.2                // l
    ,95.2, 21.3                               // a, b
  };

  for ( auto& value : data )
    raw_data.write( reinterpret_cast<const char*>( &value ), sizeof( double ) );

  raw_data.close();
}

// прочитать одно число типа double из файла
inline double read_double( std::istream & data )
{
  double buf = 0.0;
  data.read( reinterpret_cast<char*>( &buf ), sizeof( double ) );
  return buf;
}

// получить i-ый элемент
inline double get_n( std::istream & data, const size_t i )
{
  data.seekg( i * sizeof( double ), data.beg );
  return ::read_double( data );
}

// получить i-ый x
inline double get_x( std::istream & data, const size_t i )
{
  return ::get_n( data, i );
}

// получить i-ый l
inline double get_l( std::istream & data, const size_t i )
{
  return ::get_n( data, ( i + 7 ) );
}

// получить a
inline double get_a( std::istream & data )
{
  return ::get_n( data, ( 12 ) );
}

// получить b
inline double get_b( std::istream & data )
{
  return ::get_n( data, ( 13 ) );
}

// получить s
inline const double get_s( std::istream & data )
{
  double sum_x = 0.0;
  double sum_l = 0.0;

  const double a = ::get_a( data );
  const double b = ::get_b( data );

  for ( size_t i = 0; i < 7; ++i )
    sum_x += ( ::get_x( data, i ) - a*b );

  for ( size_t i = 0; i < 5; ++i )
    sum_l += ( ::get_l( data, i ) - a );

  return sum_x / sum_l;
}

// получить p i-ое
inline const double get_p_i( std::istream & data, const size_t i )
{
  return ::get_s( data ) * ::get_l( data, i );;
}
/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  ::setlocale( NULL, "" ); // заставляем консоль говорить по-русски

  const std::string file_name = "data.bin"; // имя файла с данными.
  ::fill_file( file_name );                 // заполнение файла данными

  std::ifstream raw_data( file_name, std::ios::binary ); // открываем на чтение

  std::cout << "a: " << ::get_a( raw_data ) << std::endl;
  std::cout << "b: " << ::get_b( raw_data ) << std::endl;

  std::cout << "l 5: " << ::get_l( raw_data, 4 ) << std::endl;
  std::cout << "x 7: " << ::get_x( raw_data, 6 ) << std::endl;

  std::cout << "l 1: " << ::get_l( raw_data, 0 ) << std::endl;
  std::cout << "x 1: " << ::get_x( raw_data, 0 ) << std::endl;


  std::cout << "s : " << ::get_s( raw_data ) << std::endl;


  std::cout << "p 1 : " << ::get_p_i( raw_data, 0 ) << std::endl;
  std::cout << "p 3 : " << ::get_p_i( raw_data, 2 ) << std::endl;
  std::cout << "p 5 : " << ::get_p_i( raw_data, 4 ) << std::endl;


  return EXIT_SUCCESS;
}