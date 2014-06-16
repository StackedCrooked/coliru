#include <algorithm>
#include <stdint.h>


class Cube3x3
{
public:
    union CornerData
    {
        uint8_t  mData8[8];
        uint16_t mData16[4];
        uint32_t mData32[2];
        uint64_t mData64;
    };

    union EdgeData
    {
        uint8_t  mData8[12];
        uint32_t mData32[3];
    };

    CornerData mCorners;
    EdgeData mEdges;

    static const Cube3x3 sSolved;
};


Cube3x3 initialize() {
    Cube3x3 cube;
    std::fill(&cube.mCorners.mData8[0], &cube.mCorners.mData8[8], 0);
    std::fill(&cube.mEdges.mData8[0], &cube.mEdges.mData8[8], 0);
    
    return cube;
}


const Cube3x3 Cube3x3::sSolved = initialize();


int main()
{
}
