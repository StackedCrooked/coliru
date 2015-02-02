#include <iostream>

#pragma pack(push, 1)
struct BITMAPFILEHEADER              // File header
{
    char bfType[2];                   // File type: should be BM ( 0x42 0x4D ) 
    int bfSize;                       // File size in bytes
    short bfReserved1;                // Reserved - for what i have no idea :P 
    short bfReserved2;                // -||-
    int bfOffBits;                    // Offset, adress of the beginning of the information about image (pixels )
};
#pragma pack(pop)

struct BITMAPFILEHEADER_nopacking     // File header
{
    char bfType[2];                   // File type: should be BM ( 0x42 0x4D ) 
    int bfSize;                       // File size in bytes
    short bfReserved1;                // Reserved - for what i have no idea :P 
    short bfReserved2;                // -||-
    int bfOffBits;                    // Offset, adress of the beginning of the information about image (pixels )
};
 
int main()
{
  std::cout << sizeof(BITMAPFILEHEADER) << '\n';
  std::cout << sizeof(BITMAPFILEHEADER_nopacking) << '\n';
}
