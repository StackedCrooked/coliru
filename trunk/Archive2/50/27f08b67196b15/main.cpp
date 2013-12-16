#include <iostream>
#include <sstream>
#include <string>

std::string byteToHex( unsigned char input )
{
  std::stringstream ret;

  unsigned char hi = ( input & 0xF0 ) >> 4;
  unsigned char lo = ( input & 0x0F );

    std::cout << ( int )hi << " - " << ( int )lo << std::endl;
    
  hi += 0x30;
  lo += 0x30;
  
    std::cout << ( int )hi << " - " << ( int )lo << std::endl;
    
  if ( hi > 0x57 ) // Letter
  {
    hi += 0x27;
  }

  if ( lo > 0x57 )
  {
    lo += 0x27;
  }
    std::cout << ( int )hi << " - " << ( int )lo << std::endl;
  
  ret << hi << lo;
  
  return ret.str(  );
}

int main( int argc, char **argv )
{
    std::cout << byteToHex( 9 );
    
    return 0;
}