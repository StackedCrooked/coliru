///////////////////////////////////////////////////////////////////////////////////////////
////                                        Лист 2
///////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <ios>
#include <algorithm>
#include <tuple>


/////////////////////////////////////////////////////////////////////////////////////////
//                                        Задание 6
/////////////////////////////////////////////////////////////////////////////////////////

// заполнить файл значениями
void fill_file( const std::string & file_name )
{
  std::ofstream raw_data( file_name, std::ios::binary );

  for ( size_t i = 0; i < 40; ++i )
  {
    double value = ::rand() * 0.01 * ( ::rand() % 2 ? -1 : 1 );
    raw_data.write( reinterpret_cast<const char*>( &value ), sizeof( double ) );
  }

  raw_data.close();
}

// прочитать одно число типа double из файла
inline double read_double( std::istream & data )
{
  double buf = 0.0;
  data.read( reinterpret_cast<char*>( &buf ), sizeof( double ) );
  return buf;
}

// записать одно число типа double в файл
inline void write_double( std::iostream & data, const size_t i, const double val )
{
  data.seekg( i * sizeof( double ), data.beg );
  data.write( reinterpret_cast<const char*>( &val ), sizeof( double ) );
}

// получить i-ый элемент. нумерация с 0
inline double get_n( std::istream & data, const size_t i )
{
  data.seekg( i * sizeof( double ), data.beg );
  return ::read_double( data );
}

// минимальный элемент
inline size_t get_min( std::istream & data )
{
  size_t min_i = 0;

  double min = ::get_n( data, min_i );
  double current_val = min;

  for ( size_t i = 0; i < 40; ++i )
  {
    current_val = ::get_n( data, i );
    if ( current_val < min )
    {
      min = current_val;
      min_i = i;
    }
  }

  return min_i;
}

// max элемент
inline size_t get_max( std::istream & data )
{
  size_t max_i = 0;

  double max = ::get_n( data, max_i );
  double current_val = max;

  for ( size_t i = 0; i < 40; ++i )
  {
    current_val = ::get_n( data, i );
    if ( current_val > max )
    {
      max = current_val;
      max_i = i;
    }
  }

  return max_i;
}

// вывести все значения
inline void print_vals( std::istream & data )
{
  for ( size_t i = 0; i < 40; ++i )
    std::cout << ::get_n( data, i ) << " ";

  std::cout << std::endl;
}

// заполнить диапазон [a;b) значением
inline void fill( std::iostream & data, const size_t a, const size_t b, const double val )
{
  size_t begin = 0;
  size_t end   = 0;

  std::tie( begin, end ) = std::minmax( a, b );

  for ( size_t i = begin; i < end; i++ )
    ::write_double( data, i, val );
}

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  ::setlocale( NULL, "" ); // заставляем консоль говорить по-русски

  const std::string file_name = "data.bin"; // имя файла с данными.
  ::fill_file( file_name );                 // заполнение файла значениями

  std::fstream raw_data( file_name, std::ios::binary | std::ios::in | std::ios::out ); // открываем на чтение и запись

  std::cout << "Исходные данные: " << std::endl;
  ::print_vals( raw_data );

  size_t min_i = ::get_min( raw_data ); // позиция максимального и минимального элемента
  size_t max_i = ::get_max( raw_data );

  std::cout << std::endl;
  std::cout << "min elem pos: " << min_i << " value: " << ::get_n( raw_data, min_i ) << std::endl;
  std::cout << "max elem pos: " << max_i << " value: " << ::get_n( raw_data, max_i ) << std::endl;
  std::cout << std::endl;

  ::fill( raw_data, min_i, max_i, 0 );

  std::cout << "Измененные данные: " << std::endl;
  ::print_vals( raw_data );

  return EXIT_SUCCESS;
}
