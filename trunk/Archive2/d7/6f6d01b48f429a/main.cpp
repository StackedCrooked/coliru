#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <ios>

/////////////////////////////////////////////////////////////////////////////////////////
//                                        Задание 6
/////////////////////////////////////////////////////////////////////////////////////////

// заполнить файл значениями
void fill_file( const std::string & file_name )
{
  std::ofstream raw_data( file_name, std::ios::binary );

  for ( size_t i = 0; i < 100; ++i )
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

  for ( size_t i = 0; i < 100; ++i )
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

// сумма элементов [a;b)
inline double get_sum( std::istream & data, const size_t a, const size_t b )
{
  double sum = 0.0;

  for ( size_t i = a; i < b; ++i )
    sum += ::get_n( data, i );

  return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
  const std::string file_name = "data.bin"; // имя файла с данными.
  ::fill_file( file_name );                 // заполнение файла данными

  std::ifstream raw_data( file_name, std::ios::binary ); // открываем на чтение
  std::cout << ::get_sum( raw_data, 0, ::get_min( raw_data ) );

  return EXIT_SUCCESS;
}
