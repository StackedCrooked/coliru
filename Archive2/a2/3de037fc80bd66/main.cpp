#include <stdio.h>
#include <stdlib.h>

#define POLY_CRC16  0xa001
#define INIT_CRC16  0

unsigned short checksum_crc16(unsigned char *in, int length)
{
  register unsigned short crc, bit;
  register int i;

  crc = INIT_CRC16;
  while(length-- > 0) {
    for (i=1; i <= 0x80; i<<=1) {
      bit = (((*in)&i)?0x8000:0);
      if (crc & 1) bit ^= 0x8000;
      crc >>= 1;
      if (bit) crc ^= (int)(POLY_CRC16);
      }
    ++in;
  }
  return crc;
}

int main( int argc, char *argv[] ) {

  unsigned char test[] = "abcd";

  fprintf( stdout, "check '%s' of size %lu output: %u\n", "lol", sizeof test, checksum_crc16( test, sizeof test ) );

  exit( EXIT_SUCCESS );
}