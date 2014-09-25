#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

uint16_t checksum(const unsigned char * data, unsigned char length)
{
  uint16_t crc = 0xFFFF;
  uint16_t polynome = 0xA001;
  unsigned int cptOctet = 0;
  unsigned int cptBit = 0;
  uint16_t parity= 0;

  for(cptOctet= 0; cptOctet < length; cptOctet++)
  {
    crc ^= uint8_t(*(data + cptOctet));
    for(cptBit = 0; cptBit <= 7; cptBit++)
    {
      parity = crc;
      crc >>= 1;
      if(parity%2 == true) crc ^= polynome;
    }
  }
  return crc;   
}

int main()
{
    
    // AA 54 60 EB 8A 16 18 01 00 03 00 00 00
    unsigned char buffer[] = { 
        0xAA, 0x54, 0x60, 0xEB,
        0x8A, 0x16, 0x18, 0x01,
        0x00, 0x03, 0x00, 0x00,
        0x00  };
    std::cout << std::hex << static_cast<unsigned int>(checksum(buffer + 3, 10)) << std::endl;
    return 0;
}
