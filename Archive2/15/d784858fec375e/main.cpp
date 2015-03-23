unsigned short checksum_crc16(unsigned char *in, int length) { /* do stuff */ }

int main( int argc, char *argv[] ) {
  unsigned char test[] = "abcd";
  checksum_crc16( &test, sizeof test );
}