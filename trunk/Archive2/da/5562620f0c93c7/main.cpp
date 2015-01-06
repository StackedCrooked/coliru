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
    10.1, 11.3, 45.5, 41.3, 425.6 // x
    ,12.6, 21.5, 95.2, 21.3, 5.2  // y
    ,30.4, 1.5, 5.71, 1.3, 5.2  // z
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

// получить i-ый y
inline double get_y( std::istream & data, const size_t i )
{
  return ::get_n( data, ( i + 5 ) );
}

// получить i-ый z
inline double get_z( std::istream & data, const size_t i )
{
  return ::get_n( data, ( i + 10 ) );
}

// получить a i-ое
inline const double get_a_i( std::istream & data, const size_t i )
{
  return ::sqrt( ::abs( ::get_x( data, i ) * ::get_y( data, i ) * ::get_z( data, i ) ) );
}

// получить b
inline const double get_b( std::istream & data )
{
  double sum = 0.0;
  for ( size_t i = 0; i < 5; ++i )
    sum = ::sqr( ::get_x( data, i ) - ::get_y( data, i ) );
  return sum;
}
/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  ::setlocale( NULL, "" ); // заставляем консоль говорить по-русски

  const std::string file_name = "data.bin"; // имя файла с данными.
  ::fill_file( file_name );                 // заполнение файла данными

  std::ifstream raw_data( file_name, std::ios::binary ); // открываем на чтение

  // проверка для a i
  std::cout << "Получить a i-ое:" << std::endl;
  std::cout << "a 4: " << ::get_a_i( raw_data, 4 ) << std::endl;
  std::cout << "a 2: " << ::get_a_i( raw_data, 2 ) << std::endl;
  std::cout << "a 0: " << ::get_a_i( raw_data, 0 ) << std::endl;

  std::cout << std::endl;

  // проверка для b
  std::cout << "Получить b:" << std::endl;
  std::cout << get_b( raw_data ) << std::endl;

  return EXIT_SUCCESS;
}