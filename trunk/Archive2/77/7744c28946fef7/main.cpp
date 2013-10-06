#include <iostream>


struct BitmapHeader {
        // BMP header total size 14 bytes
        std::uint16_t signature;
        std::uint32_t fileSize;
        std::uint16_t reservedOne;
        std::uint16_t reservedTwo;
        std::uint32_t pixelArrayOffset;
        // DIB header
        std::uint32_t dibHeaderSize;
        std::uint32_t width;
        std::uint32_t height;
        std::uint16_t nColorPlanes;
        std::uint16_t bitsPerPixel;
        std::uint32_t compression;
        std::uint32_t rawDataSize;
        std::uint32_t horizontalRes; // pixels / meter
        std::uint32_t verticalRes; // pixels / meter
        std::uint32_t numColors;
        std::uint32_t importantColors;
    } __attribute__ ( (__packed__, __aligned__(4)));

int main()
{
    std::cout << sizeof(BitmapHeader) << '\n' << alignof(BitmapHeader);
}



