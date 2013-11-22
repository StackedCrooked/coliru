#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

template < typename T >
inline bool isOdd( T value )
{
  if ( ( value & 1 ) > 0 )
  {
    return true;
  }

  return false;
}

unsigned char asciiToByte( const char * const ascii )
{
  unsigned char ret = 0;
  unsigned char temp[ 2 ] = { 0 };
  memcpy( temp, ascii, 2 );

  if ( temp[ 0 ] > 0x39 ) // Is not numeric
  {
    // Convert to uppercase
    temp[ 0 ] &= 0xDF;

    // Convert ascii to hex byte
    temp[ 0 ] -= 0x37;

    // Set as high order nibble
    ret = ( temp[ 0 ] <<= 4 );
  }

  if ( temp[ 1 ] > 0x39 ) // Is not numeric
  {
    // Convert to uppercase
    temp[ 1 ] &= 0xDF;

    // Convert ascii to hex byte
    temp[ 1 ] -= 0x37;

    // Set as high order nibble
    ret += ( temp[ 1 ] & 0x0F );
  }

  return ret;
}

int hexStringToByte( const char * const string, unsigned char* output )
{
  if ( output == NULL )
  {
    return -1;
  }

  if ( string == NULL )
  {
    return -1;
  }

  int length = strlen( string );

  for ( int i = 0; i < length; i++ )
  {
    output[ i ] = asciiToByte( &string[ i * 2 ] );
  }

  return -1;
}

int main( int argc, char **argv )
{    
    char data[] = "A000000003";
    unsigned char out[] = new unsigned char[ sizeof( "A000000003" ) / 2 ];
    hexStringToByte( data, out )
    
    for ( int i = 0; i < sizeof( "A000000003" ) / 2; ++i )
    {
        std::cout << std::hex << std::setfill( '0' ) << std::setw( 2 ) << ( int )out[ i ] << std::endl;
    }
 
    return 0;
}